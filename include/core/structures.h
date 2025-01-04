#ifndef ASSISTANT_CORE_STRUCTURES_H
#define ASSISTANT_CORE_STRUCTURES_H

#include <opencv2/core/types.hpp>
#include "core/models.h"
#include "core/algorithms.h"
#include "core/app.h"

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
        Model detectionModel;
        Model mattingModel;
        bool blur = false;
        bool idPhoto = false;
        bool autosave = false;
        const char *outputPath{"./out"};
        Core::Backend backend = Core::Backend::CPU;

        bool operator!=(const Params &other) const {
            return detectionModel != other.detectionModel || idPhoto != other.idPhoto || backend != other.backend;
        }
    };

    struct Point {
        cv::Point pt{};
        float confidence{0.0f};
    };

    struct Detection {
        float confidence{0.0f};
        cv::Rect box{};
        Point rightEye{};
        Point leftEye{};
        Point nose{};
        Point mouthRightCorner{};
        Point mouthLeftCorner{};

        Detection(float confidence, cv::Rect box) : confidence(confidence), box(box) {
        }

        Detection(
            float confidence,
            cv::Rect box,
            Point rightEye,
            Point leftEye,
            Point nose,
            Point mouthRightCorner,
            Point mouthLeftCorner
        ) : confidence(confidence),
            box(box),
            rightEye(rightEye),
            leftEye(leftEye),
            nose(nose),
            mouthRightCorner(mouthRightCorner),
            mouthLeftCorner(mouthLeftCorner) {
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
        Core::Backend backend = Core::Backend::CPU;

        bool operator!=(const Params &other) const {
            return model != other.model || backend != other.backend;
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

namespace Sd {
    struct Params {
        const char *path{"./data"};
        MultiModel model;
        int steps{20};
        bool autosave = false;
        const char *outputPath{"./out"};

        bool operator!=(const Params &other) const {
            return model != other.model;
        }
    };
}

#endif //ASSISTANT_CORE_STRUCTURES_H
