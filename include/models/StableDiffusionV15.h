#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H

#include "models/StableDiffusionModel.h"

class StableDiffusionV15 : public StableDiffusionModel {
public:
    explicit StableDiffusionV15(const std::string &modelPath, ProgressInterface *progress);

    cv::Mat generate(const std::string &text, const int &steps) override;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H
