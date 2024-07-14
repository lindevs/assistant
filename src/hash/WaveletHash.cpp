#include "hash/WaveletHash.h"
#include "utils/ImgResize.h"
#include "utils/ImgProc.h"

cv::Mat WaveletHash::calculate(const cv::Mat &input) {
    cv::Mat img = ImgResize::resize(input, cv::Size(256, 256), ImgResize::INTERPOLATION_LANCZOS);
    ImgProc::bgr2gray(img, img);
    ImgProc::scale(img);
    cv::Mat temp;
    ImgProc::dwt2(img, temp, 5);
    img = temp(cv::Rect(0, 0, 8, 8));

    auto *data = (float *) img.clone().data;
    std::sort(data, data + 64);
    img = img >= (data[31] + data[32]) / 2.0f;

    cv::Mat hash(1, 8, CV_8U);
    ImgProc::hash(img , hash);

    return hash;
}
