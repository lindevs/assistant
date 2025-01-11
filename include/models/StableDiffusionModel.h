#ifndef ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H
#define ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H

#include <stable-diffusion.h>
#include <opencv2/core/mat.hpp>
#include "models/ProgressInterface.h"

class StableDiffusionModel {
public:
    StableDiffusionModel(
        const std::string &modelPath,
        const std::string &cliplPath,
        const std::string &clipgPath,
        const std::string &t5xxlPath,
        const std::string &vaePath,
        ProgressInterface *progress
    );

    virtual ~StableDiffusionModel();

    virtual cv::Mat generate(const std::string &text, const int &steps) = 0;

protected:
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

    cv::Mat createImage(sd_image_t *result);
};

#endif //ASSISTANT_MODELS_STABLE_DIFFUSION_MODEL_H
