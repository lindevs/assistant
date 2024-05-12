#include "ocr/QTesseract.h"

void QTesseract::start(const Ocr::Params &params) {
    tesseract.start(params);
}

void QTesseract::stop() {
    tesseract.stop();
}

void QTesseract::recognize(const cv::Mat &img) {
    emit recognized(tesseract.recognize(img.data, img.cols, img.rows, img.channels(), (int) img.step));
}
