#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>
#include "qr/ZxingCpp.h"

QImage ZxingCpp::generate(const std::string &text, const Qr::Params &params) {
    auto writer = ZXing::MultiFormatWriter(ZXing::BarcodeFormat::QRCode);
    auto matrix = writer.encode(text, params.width, params.height);
    auto bitmap = ZXing::ToMatrix<uint8_t>(matrix);

    return QImage(
        bitmap.data(),
        bitmap.width(),
        bitmap.height(),
        bitmap.width(),
        QImage::Format::Format_Grayscale8
    ).copy();
}
