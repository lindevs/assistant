#include "utils/ImgResize.h"
#include <iostream>

cv::Mat ImgResize::resize(const cv::Mat &src, const cv::Size &size, int32_t filter) {
    const cv::Vec4f rect(0.0f, 0.0f, static_cast<float>(src.size().width), static_cast<float>(src.size().height));

    const int32_t xSize = size.width;
    const int32_t ySize = size.height;

    if (filter == INTERPOLATION_NEAREST) {
        return resampleNearest(src, xSize, ySize, rect);
    }

    std::shared_ptr<Filter> filterP;
    switch (filter) {
        case INTERPOLATION_BOX:
            filterP = std::make_shared<BoxFilter>(BoxFilter());
            break;
        case INTERPOLATION_BILINEAR:
            filterP = std::make_shared<BilinearFilter>(BilinearFilter());
            break;
        case INTERPOLATION_HAMMING:
            filterP = std::make_shared<HammingFilter>(HammingFilter());
            break;
        case INTERPOLATION_BICUBIC:
            filterP = std::make_shared<BicubicFilter>(BicubicFilter());
            break;
        case INTERPOLATION_LANCZOS:
            filterP = std::make_shared<LanczosFilter>(LanczosFilter());
            break;
        default:
            throw std::runtime_error("unsupported resampling filter");
    }

    return ImgResize::resample(src, xSize, ySize, filterP, rect);
}

double ImgResize::BoxFilter::filter(double x) const {
    if (x > -0.5 && x <= 0.5) {
        return 1.0;
    }

    return 0.0;
}

double ImgResize::BilinearFilter::filter(double x) const {
    if (x < 0.0) {
        x = -x;
    }
    if (x < 1.0) {
        return 1.0 - x;
    }

    return 0.0;
}

double ImgResize::HammingFilter::filter(double x) const {
    if (x < 0.0) {
        x = -x;
    }
    if (x == 0.0) {
        return 1.0;
    }
    if (x >= 1.0) {
        return 0.0;
    }
    x = x * M_PI;

    return sin(x) / x * (0.54 + 0.46 * cos(x));
}

double ImgResize::BicubicFilter::filter(double x) const {
    constexpr double a = -0.5;
    if (x < 0.0) {
        x = -x;
    }
    if (x < 1.0) {
        return ((a + 2.0) * x - (a + 3.0)) * x * x + 1;
    }
    if (x < 2.0) {
        return (((x - 5) * x + 8) * x - 4) * a;
    }

    return 0.0;
}

double ImgResize::LanczosFilter::sincFilter(double x) {
    if (x == 0.0) {
        return 1.0;
    }
    x = x * M_PI;

    return sin(x) / x;
}

double ImgResize::LanczosFilter::filter(double x) const {
    if (-3.0 <= x && x < 3.0) {
        return sincFilter(x) * sincFilter(x / 3);
    }

    return 0.0;
}

cv::Mat ImgResize::resample(const cv::Mat &imIn, int32_t xSize, int32_t ySize,
                         const std::shared_ptr<Filter> &filterP, const cv::Vec4f &rect
) {
    cv::Mat imOut;
    cv::Mat imTemp;

    std::vector<int32_t> boundsHoriz;
    std::vector<int32_t> boundsVert;
    std::vector<double> kkHoriz;
    std::vector<double> kkVert;

    const bool needHorizontal = xSize != imIn.size().width || rect[0] != 0.0f || static_cast<int32_t>(rect[2]) != xSize;
    const bool needVertical = ySize != imIn.size().height || rect[1] != 0.0f || static_cast<int32_t>(rect[3]) != ySize;

    const int32_t ksizeHoriz = precomputeCoeffs(
        imIn.size().width, rect[0], rect[2], xSize, filterP, boundsHoriz, kkHoriz
    );
    const int32_t ksizeVert = precomputeCoeffs(
        imIn.size().height, rect[1], rect[3], ySize, filterP, boundsVert, kkVert
    );

    const int32_t yboxFirst = boundsVert[0];
    const int32_t yboxLast = boundsVert[ySize * 2 - 2] + boundsVert[ySize * 2 - 1];

    if (needHorizontal) {
        for (int32_t i = 0; i < ySize; ++i) {
            boundsVert[i * 2] -= yboxFirst;
        }

        imTemp.create(yboxLast - yboxFirst, xSize, imIn.type());
        if (!imTemp.empty()) {
            resampleHorizontal(imTemp, imIn, yboxFirst, ksizeHoriz, boundsHoriz, kkHoriz);
        } else {
            return {};
        }
        imOut = imTemp;
    }

    if (needVertical) {
        const auto newW = imTemp.size().width != 0 ? imTemp.size().width : xSize;
        imOut.create(ySize, newW, imIn.type());
        if (!imOut.empty()) {
            if (imTemp.empty()) {
                imTemp = imIn;
            }

            resampleVertical(imOut, imTemp, ksizeVert, boundsVert, kkVert);
        } else {
            return {};
        }
    }

    if (imOut.empty()) {
        imOut = imIn;
    }

    return imOut;
}

void ImgResize::resampleHorizontal(cv::Mat &imOut, const cv::Mat &imIn, int32_t offset, int32_t ksize,
                                const std::vector<int32_t> &bounds, const std::vector<double> &prekk
) {
    switch (imIn.depth()) {
        case CV_8U:
            return resampleHorizontal<uint8_t>(
                imOut, imIn, offset, ksize, bounds, prekk, normalizeCoeffs8bpc,
                static_cast<double>(1U << (precisionBits - 1U)), clip8);
        case CV_32F:
            return resampleHorizontal<float>(imOut, imIn, offset, ksize, bounds, prekk);
        default:
            throw std::runtime_error("Image type is not supported");
    }
}

template<typename T>
void ImgResize::resampleHorizontal(cv::Mat &imOut, const cv::Mat &imIn, int32_t offset, int32_t ksize,
                                const std::vector<int32_t> &bounds, const std::vector<double> &prekk,
                                preprocessCoefficientsFn preprocessCoefficients, double initBuffer,
                                outMapFn<T> outMap
) {
    std::vector<double> kk(prekk.begin(), prekk.end());
    if (preprocessCoefficients != nullptr) {
        kk = preprocessCoefficients(kk);
    }

    for (int32_t yy = 0; yy < imOut.size().height; ++yy) {
        for (int32_t xx = 0; xx < imOut.size().width; ++xx) {
            const int32_t xmin = bounds[xx * 2 + 0];
            const int32_t xmax = bounds[xx * 2 + 1];
            const double *k = &kk[xx * ksize];
            for (int32_t c = 0; c < imIn.channels(); ++c) {
                double ss = initBuffer;
                for (int32_t x = 0; x < xmax; ++x) {
                    ss += static_cast<double>(imIn.ptr<T>(yy + offset, x + xmin)[c]) * k[x];
                }
                imOut.ptr<T>(yy, xx)[c] = outMap == nullptr ? static_cast<T>(ss) : outMap(ss);
            }
        }
    }
}

void ImgResize::resampleVertical(cv::Mat &imOut, const cv::Mat &imIn, int32_t ksize,
                              const std::vector<int32_t> &bounds, const std::vector<double> &prekk
) {
    imOut = imOut.t();
    resampleHorizontal(imOut, imIn.t(), 0, ksize, bounds, prekk);
    imOut = imOut.t();
}

cv::Mat ImgResize::resampleNearest(const cv::Mat &imIn, int32_t xSize, int32_t ySize, const cv::Vec4f &rect) {
    auto rx0 = static_cast<int32_t>(rect[0]);
    auto ry0 = static_cast<int32_t>(rect[1]);
    auto rx1 = static_cast<int32_t>(rect[2]);
    auto ry1 = static_cast<int32_t>(rect[3]);
    rx0 = std::max(rx0, 0);
    ry0 = std::max(ry0, 0);
    rx1 = std::min(rx1, imIn.size().width);
    ry1 = std::min(ry1, imIn.size().height);

    cv::Mat m = cv::Mat::zeros(2, 3, CV_64F);
    m.at<double>(0, 0) = static_cast<double>(rx1 - rx0) / static_cast<double>(xSize);
    m.at<double>(0, 2) = static_cast<double>(rx0);
    m.at<double>(1, 1) = static_cast<double>(ry1 - ry0) / static_cast<double>(ySize);
    m.at<double>(1, 2) = static_cast<double>(ry0);

    cv::Mat imOut = cv::Mat::zeros(ySize, xSize, imIn.type());

    size_t pixelSize;
    switch (imIn.depth()) {
        case CV_8U:
            pixelSize = sizeof(uint8_t);
            break;
        case CV_32F:
            pixelSize = sizeof(float);
            break;
        default:
            throw std::runtime_error("Image type is not supported");
    }
    pixelSize *= imIn.channels();

    const int32_t x0 = 0;
    const int32_t y0 = 0;
    const int32_t x1 = xSize;
    const int32_t y1 = ySize;

    double xo = m.at<double>(0, 2) + m.at<double>(0, 0) * 0.5;
    double yo = m.at<double>(1, 2) + m.at<double>(1, 1) * 0.5;

    auto coord = [](double x) -> int32_t {
        return x < 0.0 ? -1 : static_cast<int32_t>(x);
    };

    std::vector<int> xintab;
    xintab.resize(imOut.size().width);

    int32_t xmin = x1;
    int32_t xmax = x0;
    for (int32_t x = x0; x < x1; ++x) {
        int32_t xin = coord(xo);
        if (xin >= 0 && xin < imIn.size().width) {
            xmax = x + 1;
            if (x < xmin) {
                xmin = x;
            }
            xintab[x] = xin;
        }
        xo += m.at<double>(0, 0);
    }

    for (int32_t y = y0; y < y1; ++y) {
        int32_t yi = coord(yo);
        if (yi >= 0 && yi < imIn.size().height) {
            for (int32_t x = xmin; x < xmax; ++x) {
                memcpy(imOut.ptr(y, x), imIn.ptr(yi, xintab[x]), pixelSize);
            }
        }
        yo += m.at<double>(1, 1);
    }

    return imOut;
}

int32_t ImgResize::precomputeCoeffs(int32_t inSize, double in0, double in1, int32_t outSize,
                                 const std::shared_ptr<Filter> &filterP, std::vector<int32_t> &bounds,
                                 std::vector<double> &kk
) {
    const double scale = (in1 - in0) / static_cast<double>(outSize);
    double filterscale = scale;
    if (filterscale < 1.0) {
        filterscale = 1.0;
    }

    const double support = filterP->getSupport() * filterscale;

    const auto kSize = static_cast<int32_t>(ceil(support)) * 2 + 1;

    if (outSize > INT32_MAX / (kSize * static_cast<int32_t>(sizeof(double)))) {
        throw std::runtime_error("Memory error");
    }

    kk.resize(outSize * kSize);

    bounds.resize(outSize * 2);

    int32_t x;
    constexpr double halfPixel = 0.5;
    for (int32_t xx = 0; xx < outSize; ++xx) {
        double center = in0 + (xx + halfPixel) * scale;
        double ww = 0.0;
        double ss = 1.0 / filterscale;

        auto xmin = static_cast<int32_t>(center - support + halfPixel);
        if (xmin < 0) {
            xmin = 0;
        }

        auto xmax = static_cast<int32_t>(center + support + halfPixel);
        if (xmax > inSize) {
            xmax = inSize;
        }
        xmax -= xmin;
        double *k = &kk[xx * kSize];
        for (x = 0; x < xmax; ++x) {
            double w = filterP->filter((x + xmin - center + halfPixel) * ss);
            k[x] = w;
            ww += w;
        }
        for (x = 0; x < xmax; ++x) {
            if (ww != 0.0) {
                k[x] /= ww;
            }
        }

        for (; x < kSize; ++x) {
            k[x] = 0;
        }
        bounds[xx * 2 + 0] = xmin;
        bounds[xx * 2 + 1] = xmax;
    }

    return kSize;
}

std::vector<double> ImgResize::normalizeCoeffs8bpc(const std::vector<double> &prekk) {
    std::vector<double> kk;
    kk.reserve(prekk.size());

    constexpr auto shiftedCoeff = static_cast<double>(1U << precisionBits);

    for (const auto &k: prekk) {
        if (k < 0) {
            kk.emplace_back(trunc(-0.5 + k * shiftedCoeff));
        } else {
            kk.emplace_back(trunc(0.5 + k * shiftedCoeff));
        }
    }

    return kk;
}

uint8_t ImgResize::clip8(double in) {
    auto saturateVal = static_cast<intmax_t>(in) >> precisionBits;
    if (saturateVal < 0) {
        return 0;
    }
    if (saturateVal > UINT8_MAX) {
        return UINT8_MAX;
    }

    return static_cast<uint8_t>(saturateVal);
}
