#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>
#include "qr/ZxingCpp.h"

cv::Mat ZxingCpp::generate(const std::string &text, const Qr::Params &params) {
    auto writer = ZXing::MultiFormatWriter(ZXing::BarcodeFormat::QRCode);
    auto matrix = writer.encode(text, params.width, params.height);

    int width = matrix.width();
    int height = matrix.height();
    cv::Mat img(height, width, CV_8UC1);
    for (int y = 0; y < height; ++y) {
        int idx = img.cols * y;
        for (int x = 0; x < width; ++x) {
            *(img.data + (idx + x)) = matrix.get(x, y) ? 0 : 255;
        }
    }

    return img;
}
