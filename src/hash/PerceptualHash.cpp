#include "hash/PerceptualHash.h"
#include "utils/ImgResize.h"
#include "utils/ImgProc.h"

cv::Mat PerceptualHash::calculate(const cv::Mat &input) {
    cv::Mat img = ImgResize::resize(input, cv::Size(32, 32), ImgResize::INTERPOLATION_LANCZOS);
    ImgProc::bgr2gray(img, img);
    ImgProc::convertToFloat(img);
    ImgProc::dct(img, img);
    img = img(cv::Rect(0, 0, 8, 8));

    auto *data = (float *) img.clone().data + 1;
    std::nth_element(data, data + 31, data + 63);
    img = img >= data[31];

    cv::Mat hash(1, 8, CV_8U);
    ImgProc::hash(img , hash);

    return hash;
}
