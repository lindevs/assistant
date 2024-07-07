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

cv::Scalar ImgProc::mean(const cv::Mat &src) {
    return cv::mean(src);
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
