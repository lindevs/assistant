#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_3_MEDIUM_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_3_MEDIUM_H

#include "models/StableDiffusionModel.h"

class StableDiffusion3Medium : public StableDiffusionModel {
public:
    explicit StableDiffusion3Medium(const std::string &modelPath, ProgressInterface *progress);

    cv::Mat generate(const std::string &text, const int &steps) override;

protected:
    const float cfgScale = 4.5f;
    const int width = 1024;
    const int height = 1024;
    const sample_method_t sampleMethod = EULER;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_3_MEDIUM_H
