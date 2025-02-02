#include "models/StableDiffusionV15.h"

StableDiffusionV15::StableDiffusionV15(const std::string &modelPath, ProgressInterface *progress)
    : StableDiffusionModel(modelPath, "", "", "", "", "", progress) {
}

cv::Mat StableDiffusionV15::generate(const std::string &text, const int &steps) {
    sampleSteps = steps;
    sd_image_t *result = txt2img(
        sdCtx,
        text.c_str(),
        "",
        clipSkip,
        cfgScale,
        guidance,
        width,
        height,
        sampleMethod,
        sampleSteps,
        seed,
        batchCount,
        nullptr,
        controlStrength,
        styleStrength,
        normalizeInput,
        "",
        skipLayers,
        skipLayersCount,
        slgScale,
        skipLayerStart,
        skipLayerEnd
    );

    return createImage(result);
}
