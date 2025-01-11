#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_XL_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_XL_H

#include "models/StableDiffusionModel.h"

class StableDiffusionXl : public StableDiffusionModel {
public:
    explicit StableDiffusionXl(const std::string &modelPath, const std::string &vaePath, ProgressInterface *progress);

    cv::Mat generate(const std::string &text, const int &steps) override;

protected:
    const int width = 1024;
    const int height = 1024;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_XL_H
