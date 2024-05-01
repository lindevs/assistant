#ifndef ASSISTANT_QR_ZXING_CPP_H
#define ASSISTANT_QR_ZXING_CPP_H

#include <QImage>
#include "core/structures.h"

class ZxingCpp {
public:
    static QImage generate(const std::string &text, const Qr::Params &params);
};

#endif //ASSISTANT_QR_ZXING_CPP_H
