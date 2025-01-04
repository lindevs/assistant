#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_35_LARGE_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_35_LARGE_H

#include "models/StableDiffusionModel.h"

class StableDiffusion35Large : public StableDiffusionModel {
public:
    explicit StableDiffusion35Large(
        const std::string &modelPath,
        const std::string &cliplPath,
        const std::string &clipgPath,
        const std::string &t5xxlPath,
        ProgressInterface *progress
    );

    cv::Mat generate(const std::string &text, const int &steps) override;

protected:
    const float cfgScale = 4.5f;
    const int width = 1024;
    const int height = 1024;
    const sample_method_t sampleMethod = EULER;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_35_LARGE_H
