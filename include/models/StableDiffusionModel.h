#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H

#include "core/structures.h"

class StableDiffusionModel {
public:
    virtual ~StableDiffusionModel() = default;

    virtual cv::Mat generate(const std::string &text, const int &steps) = 0;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H
