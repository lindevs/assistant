#ifndef ASSISTANT_CORE_STRUCTURES_H
#define ASSISTANT_CORE_STRUCTURES_H

namespace Qr {
    struct Params {
        int width = 512;
        int height = 512;
    };
}

namespace Ocr {
    struct Params {
        const char *path = "./data/";
        const char *language = "eng";

        bool operator!=(const Params &other) const {
            return language != other.language;
        }
    };
}

#endif //ASSISTANT_CORE_STRUCTURES_H
