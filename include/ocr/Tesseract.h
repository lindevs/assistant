#ifndef ASSISTANT_OCR_TESSERACT_H
#define ASSISTANT_OCR_TESSERACT_H

#include <tesseract/baseapi.h>
#include <opencv2/core/mat.hpp>
#include "core/structures.h"

class Tesseract {
public:
    void start(const Ocr::Params &params);

    void stop();

    const char *recognize(const cv::Mat &img);

private:
    tesseract::TessBaseAPI tess;
};

#endif //ASSISTANT_OCR_TESSERACT_H
