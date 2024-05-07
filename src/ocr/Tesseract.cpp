#include "ocr/Tesseract.h"

void Tesseract::start(const Ocr::Params &params) {
    tess.Init(params.path, params.language);
}

void Tesseract::stop() {
    tess.End();
}

const char *Tesseract::recognize(const unsigned char *data, int width, int height, int channels, int steps) {
    tess.SetImage(data, width, height, channels, steps);

    return tess.GetUTF8Text();
}
