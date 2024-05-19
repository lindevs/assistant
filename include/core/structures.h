#ifndef ASSISTANT_CORE_STRUCTURES_H
#define ASSISTANT_CORE_STRUCTURES_H

#include <opencv2/core/types.hpp>

namespace Qr {
    struct Params {
        int width = 512;
        int height = 512;
        bool autosave = false;
        const char *path = "./out";
    };
}

namespace Ocr {
    struct Params {
        const char *path = "./data";
        const char *language = "eng";

        bool operator!=(const Params &other) const {
            return language != other.language;
        }
    };
}

namespace Face {
    struct Params {
        bool autosave = false;
        const char *path = "./out";
    };

    struct Detection {
        float confidence = 0.0f;
        cv::Rect box{};

        Detection(float confidence, cv::Rect box) : confidence(confidence), box(box) {
        }
    };
}

#endif //ASSISTANT_CORE_STRUCTURES_H
