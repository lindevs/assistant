#ifndef ASSISTANT_QR_ZXING_CPP_H
#define ASSISTANT_QR_ZXING_CPP_H

#include <opencv2/core/mat.hpp>
#include "core/structures.h"

class ZxingCpp {
public:
    static cv::Mat generate(const std::string &text, const Qr::Params &params);
};

#endif //ASSISTANT_QR_ZXING_CPP_H
