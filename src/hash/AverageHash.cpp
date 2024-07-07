#include "hash/AverageHash.h"
#include "utils/ImgResize.h"
#include "utils/ImgProc.h"

cv::Mat AverageHash::calculate(const cv::Mat &input) {
    cv::Mat img = ImgResize::resize(input, cv::Size(8, 8), ImgResize::INTERPOLATION_LANCZOS);
    ImgProc::bgr2gray(img, img);
    img = img > ImgProc::mean(img)[0];
    uchar *in = img.data;

    cv::Mat hash(1, 8, CV_8U);
    uchar *out = hash.data;

    size_t total = img.rows * img.cols;
    for (size_t i = 0; i != total;) {
        *out = 0;
        for (int k = 7; k >= 0; --k, ++i) {
            if (*in++) {
                *out |= 1 << k;
            }
        }
        ++out;
    }

    return hash;
}
