#include "ocr/Tesseract.h"

void Tesseract::start(const Ocr::Params &params) {
    tess.Init(params.path, params.language);
}

void Tesseract::stop() {
    tess.End();
}

const char *Tesseract::recognize(const cv::Mat &img) {
    tess.SetImage(img.data, img.cols, img.rows, img.channels(), (int) img.step);

    return tess.GetUTF8Text();
}
