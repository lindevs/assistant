#include <opencv2/imgproc.hpp>
#include "utils/ImgProc.h"

void ImgProc::hwcToNchw(const cv::Mat &src, cv::Mat &dst) {
    const int sizes[] = {1, 3, src.rows, src.cols};
    cv::Mat nchw(4, sizes, src.depth());
    cv::Mat planes[] = {
        cv::Mat(src.rows, src.cols, src.depth(), nchw.ptr(0, 2)),
        cv::Mat(src.rows, src.cols, src.depth(), nchw.ptr(0, 1)),
        cv::Mat(src.rows, src.cols, src.depth(), nchw.ptr(0, 0)),
    };
    cv::split(src, planes);

    dst = nchw;
}

void ImgProc::nms(const std::vector<cv::Rect2f> &boxes, const std::vector<float> &scores, const float &nmsThreshold,
                  std::vector<int> &indices
) {
    std::vector<std::pair<float, int> > scoreIndexPairs;
    for (size_t i = 0; i < scores.size(); ++i) {
        scoreIndexPairs.emplace_back(scores[i], i);
    }

    std::stable_sort(
        scoreIndexPairs.begin(),
        scoreIndexPairs.end(),
        [](const std::pair<float, int> &pair1, const std::pair<float, int> &pair2) {
            return pair1.first > pair2.first;
        }
    );

    for (auto &i: scoreIndexPairs) {
        bool keep = true;
        for (size_t j = 0; j < indices.size() && keep; ++j) {
            keep = jaccardIndex(boxes[i.second], boxes[indices[j]]) <= nmsThreshold;
        }
        if (keep) {
            indices.emplace_back(i.second);
        }
    }
}

void ImgProc::resize(cv::InputArray src, cv::OutputArray dst, const cv::Size &size) {
    cv::resize(src, dst, size, 0, 0, cv::INTER_LINEAR);
}

void ImgProc::letterbox(cv::InputArray src, cv::OutputArray dst, const cv::Size &size, XyScale &xyScale) {
    const auto width = (float) src.cols();
    const auto height = (float) src.rows();

    const float resizeFactor = std::min((float) size.width / width, (float) size.height / height);
    const int rw = (int) std::nearbyint(width * resizeFactor);
    const int rh = (int) std::nearbyint(height * resizeFactor);

    cv::resize(src, dst, cv::Size(rw, rh));

    const int top = (size.height - rh) / 2;
    const int bottom = size.height - rh - top;
    const int left = (size.width - rw) / 2;
    const int right = size.width - rw - left;

    cv::copyMakeBorder(dst, dst, top, bottom, left, right, cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));

    xyScale.x = (float) left;
    xyScale.y = (float) top;
    xyScale.scale = 1.0f / resizeFactor;
}

void ImgProc::scale(cv::Mat &src) {
    src.convertTo(src, CV_32F, 1.0f / 255.0f);
}

cv::Size ImgProc::scale(const cv::Size &size, float scale) {
    return {(int) ((float) size.width / scale), (int) ((float) size.height / scale)};
}

void ImgProc::convertToFloat(cv::Mat &src) {
    src.convertTo(src, CV_32F);
}

void ImgProc::normalize(cv::Mat &src, const cv::Scalar &mean, const cv::Scalar &std) {
    src = (src - mean) / std;
}

void ImgProc::scaleAndNormalize(cv::Mat &src, const float *mean, const float *std) {
    src.convertTo(src, CV_32F);
    auto *data = (float *) src.data;

    int total = src.rows * src.cols * src.channels();
    for (int i = 0; i < total; i += 3) {
        data[i] = ((data[i] / 255.0f) - mean[0]) / std[0];
        data[i + 1] = ((data[i + 1] / 255.0f) - mean[1]) / std[1];
        data[i + 2] = ((data[i + 2] / 255.0f) - mean[2]) / std[2];
    }
}

cv::Scalar ImgProc::mean(const cv::Mat &src) {
    return cv::mean(src);
}

void ImgProc::centerCrop(cv::Mat &src, const cv::Size &size) {
    src = src(
        cv::Rect(
            (int) std::nearbyint((float) (src.cols - size.width) * 0.5f),
            (int) std::nearbyint((float) (src.rows - size.height) * 0.5f),
            size.width,
            size.height
        )
    );
}

float ImgProc::jaccardIndex(const cv::Rect2f &a, const cv::Rect2f &b) {
    const float areaA = a.width * a.height;
    const float areaB = b.width * b.height;

    if (areaA + areaB <= std::numeric_limits<float>::epsilon()) {
        return 0.0f;
    }

    const cv::Rect2f ab = a & b;
    const float areaAb = ab.width * ab.height;

    return areaAb / (areaA + areaB - areaAb);
}

void ImgProc::bgr2gray(const cv::Mat &src, cv::Mat &dst) {
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
}

void ImgProc::dct(const cv::Mat &src, cv::Mat &dst) {
    cv::dct(src, dst);
}

void ImgProc::dwt2(const cv::Mat &src, cv::Mat &dst, const int level) {
    dst.create(src.rows, src.cols, CV_32F);
    auto *in = (float *) src.data;
    auto *out = (float *) dst.data;

    for (int k = 0; k < level; ++k) {
        int hStep = src.rows >> (k + 1);
        int wStep = src.cols >> (k + 1);

        for (int y = 0; y < hStep; ++y) {
            int sy0 = 2 * y * src.cols;
            int sy1 = sy0 + src.cols;
            int dy0 = y * dst.cols;
            int dy1 = dy0 + hStep * dst.cols;

            for (int x = 0; x < wStep; ++x) {
                int x2 = 2 * x;
                int sx0 = sy0 + x2;
                int sx1 = sy1 + x2;

                float s0 = in[sx0];
                float s1 = in[sx0 + 1];
                float s2 = in[sx1];
                float s3 = in[sx1 + 1];

                float sum01 = s0 + s1;
                float sum23 = s2 + s3;
                float diff01 = s0 - s1;
                float diff23 = s2 - s3;

                int dx0 = dy0 + x;
                int dx1 = dy1 + x;

                out[dx0] = (sum01 + sum23) * 0.5f;
                out[dx0 + wStep] = (diff01 - diff23) * 0.5f;
                out[dx1] = (sum01 - sum23) * 0.5f;
                out[dx1 + wStep] = (diff01 + diff23) * 0.5f;
            }
        }
        dst.copyTo(src);
    }
}

void ImgProc::hash(const cv::Mat &src, cv::Mat &dst) {
    uchar *in = src.data;
    uchar *out = dst.data;

    int size = dst.cols - 1;
    int total = src.rows * src.cols;
    for (int i = 0; i != total;) {
        *out = 0;
        for (int k = size; k >= 0; --k, ++i) {
            if (*in++) {
                *out |= 1 << k;
            }
        }
        ++out;
    }
}

std::string ImgProc::hex(const cv::Mat &src) {
    static const char *digits = "0123456789abcdef";

    uchar *data = src.data;
    size_t total = src.rows * src.cols;

    std::string dst(total * 2, '0');
    for (size_t i = 0; i < total; ++i) {
        dst[i * 2] = digits[(data[i] >> 4) & 0x0f];
        dst[i * 2 + 1] = digits[data[i] & 0x0f];
    }

    return dst;
}

double ImgProc::cosineSimilarity(const cv::Mat &x, const cv::Mat &y) {
    return x.dot(y) / std::sqrt(x.dot(x) * y.dot(y));
}
