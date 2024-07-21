#ifndef ASSISTANT_UTILS_IMG_PROC_H
#define ASSISTANT_UTILS_IMG_PROC_H

#include <opencv2/core/mat.hpp>
#include "core/structures.h"

class ImgProc {
public:
    static void hwcToNchw(const cv::Mat &src, cv::Mat &dst);

    static void nms(const std::vector<cv::Rect2f> &boxes, const std::vector<float> &scores, const float &nmsThreshold,
                    std::vector<int> &indices);

    static void letterbox(cv::InputArray src, cv::OutputArray dst, const cv::Size &size, XyScale &xyScale);

    static void scale(cv::Mat &src);

    static cv::Size scale(const cv::Size &size, float scale);

    static void convertToFloat(cv::Mat &src);

    static void scaleAndNormalize(cv::Mat &src, const float *mean, const float *std);

    static cv::Scalar mean(const cv::Mat &src);

    static void centerCrop(cv::Mat &src, const cv::Size &size);

    static float jaccardIndex(const cv::Rect2f &a, const cv::Rect2f &b);

    static void bgr2gray(const cv::Mat &src, cv::Mat &dst);

    static void dct(const cv::Mat &src, cv::Mat &dst);

    static void dwt2(const cv::Mat &src, cv::Mat &dst, int level);

    static void hash(const cv::Mat &src, cv::Mat &dst);

    static std::string hex(const cv::Mat &src);

    static double cosineSimilarity(const cv::Mat &x, const cv::Mat &y);

private:
    ImgProc() {
    }
};


#endif //ASSISTANT_UTILS_IMG_PROC_H
