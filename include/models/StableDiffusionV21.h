#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_V21_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_V21_H

#include "models/StableDiffusionModel.h"

class StableDiffusionV21 : public StableDiffusionModel {
public:
    explicit StableDiffusionV21(const std::string &modelPath, ProgressInterface *progress);

    cv::Mat generate(const std::string &text, const int &steps) override;

protected:
    const int width = 768;
    const int height = 768;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_V21_H
