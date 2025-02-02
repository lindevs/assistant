#ifndef ASSISTANT_MODELS_FLUX_1_DEV_H
#define ASSISTANT_MODELS_FLUX_1_DEV_H

#include "models/StableDiffusionModel.h"

class Flux1Dev : public StableDiffusionModel {
public:
    explicit Flux1Dev(
        const std::string &cliplPath,
        const std::string &t5xxlPath,
        const std::string &diffusionPath,
        const std::string &vaePath,
        ProgressInterface *progress
    );

    cv::Mat generate(const std::string &text, const int &steps) override;

protected:
    const float cfgScale = 1.0f;
    const int width = 1024;
    const int height = 1024;
    const sample_method_t sampleMethod = EULER;
};

#endif //ASSISTANT_MODELS_FLUX_1_DEV_H
