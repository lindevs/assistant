#include "ocr/QTesseract.h"

void QTesseract::start(const Ocr::Params &params) {
    tesseract.start(params);
}

void QTesseract::stop() {
    tesseract.stop();
}

void QTesseract::recognize(const QImage &img) {
    auto rgb = img.convertToFormat(QImage::Format_RGB888);

    emit recognized(tesseract.recognize(rgb.bits(), rgb.width(), rgb.height(), 3, (int) rgb.bytesPerLine()));
}
