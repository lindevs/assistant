#include "hash/DifferenceHash.h"
#include "utils/ImgResize.h"
#include "utils/ImgProc.h"

cv::Mat DifferenceHash::calculate(const cv::Mat &input) {
    cv::Mat img = ImgResize::resize(input, cv::Size(9, 8), ImgResize::INTERPOLATION_LANCZOS);
    ImgProc::bgr2gray(img, img);
    img = img(cv::Rect(1, 0, img.cols - 1, img.rows)) > img(cv::Rect(0, 0, img.cols - 1, img.rows));

    cv::Mat hash(1, 8, CV_8U);
    ImgProc::hash(img , hash);

    return hash;
}
