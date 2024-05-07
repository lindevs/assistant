#ifndef ASSISTANT_OCR_TESSERACT_H
#define ASSISTANT_OCR_TESSERACT_H

#include <tesseract/baseapi.h>
#include "core/structures.h"

class Tesseract {
public:
    void start(const Ocr::Params &params);

    void stop();

    const char *recognize(const unsigned char *data, int width, int height, int channels, int steps);

private:
    tesseract::TessBaseAPI tess;
};

#endif //ASSISTANT_OCR_TESSERACT_H
