#ifndef ASSISTANT_CORE_STRUCTURES_H
#define ASSISTANT_CORE_STRUCTURES_H

#include <opencv2/core/types.hpp>
#include "core/models.h"
#include "core/algorithms.h"

struct XyScale {
    float x{0.0f};
    float y{0.0f};
    float scale{0.0f};
};

namespace Qr {
    struct Params {
        int width{512};
        int height{512};
        bool autosave{false};
        const char *path{"./out"};
    };
}

namespace Ocr {
    struct Params {
        const char *path{"./data"};
        const char *language{"eng"};

        bool operator!=(const Params &other) const {
            return language != other.language;
        }
    };
}

namespace Face {
    struct Params {
        const char *path{"./data"};
        Model model;
        bool blur = false;
        bool autosave = false;
        const char *outputPath{"./out"};

        bool operator!=(const Params &other) const {
            return model != other.model;
        }
    };

    struct Detection {
        float confidence{0.0f};
        cv::Rect box{};

        Detection(float confidence, cv::Rect box) : confidence(confidence), box(box) {
        }
    };
}

namespace Hash {
    struct Params {
        Algorithm algorithm;

        bool operator!=(const Params &other) const {
            return algorithm != other.algorithm;
        }
    };
}

namespace Dedup {
    struct Params {
        const char *path{"./data"};
        Model model;

        bool operator!=(const Params &other) const {
            return model != other.model;
        }
    };

    struct Duplication {
        int index{0};
        float confidence{0.0f};

        Duplication(int index, float confidence) : index(index), confidence(confidence) {
        }
    };

    struct Findings {
        std::vector<std::string> images;
        std::vector<std::vector<Duplication>> duplications;
    };
}

#endif //ASSISTANT_CORE_STRUCTURES_H
