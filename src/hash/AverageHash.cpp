#include "hash/AverageHash.h"
#include "utils/ImgResize.h"
#include "utils/ImgProc.h"

cv::Mat AverageHash::calculate(const cv::Mat &input) {
    cv::Mat img = ImgResize::resize(input, cv::Size(8, 8), ImgResize::INTERPOLATION_LANCZOS);
    ImgProc::bgr2gray(img, img);
    img = img > ImgProc::mean(img)[0];

    cv::Mat hash(1, 8, CV_8U);
    ImgProc::hash(img , hash);

    return hash;
}
