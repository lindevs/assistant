#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H

#include <opencv2/core/mat.hpp>
#include <stable-diffusion.h>
#include "models/StableDiffusionModel.h"
#include "models/ProgressInterface.h"

class StableDiffusionV15 : public StableDiffusionModel {
public:
    explicit StableDiffusionV15(const std::string &modelPath, ProgressInterface *progress);

    ~StableDiffusionV15() override;

    cv::Mat generate(const std::string &text, const int &steps) override;

private:
    sd_ctx_t *sdCtx = nullptr;
    ProgressInterface *progress = nullptr;

    const int clipSkip = -1;
    const float cfgScale = 7.0f;
    const float guidance = 3.5f;
    const int width = 512;
    const int height = 512;
    const sample_method_t sampleMethod = EULER_A;
    int sampleSteps = 20;
    const int64_t seed = -1;
    const int batchCount = 1;
    const float controlStrength = 0.9f;
    const float styleStrength = 20.0f;
    const bool normalizeInput = false;
    int skipLayers[3] = {7, 8, 9};
    const size_t skipLayersCount = 3;
    const float slgScale = 0.0f;
    const float skipLayerStart = 0.01f;
    const float skipLayerEnd = 0.2f;
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_V15_H
