#ifndef ASSISTANT_MODELS_MATTING_MODEL_H
#define ASSISTANT_MODELS_MATTING_MODEL_H

#include "core/structures.h"

class BackgroundMattingModel {
public:
    virtual ~BackgroundMattingModel() = default;

    virtual cv::Mat generate(const cv::Mat &input) = 0;
};

#endif //ASSISTANT_MODELS_MATTING_MODEL_H
