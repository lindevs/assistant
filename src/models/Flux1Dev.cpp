#include "models/Flux1Dev.h"

Flux1Dev::Flux1Dev(
    const std::string &cliplPath,
    const std::string &t5xxlPath,
    const std::string &diffusionPath,
    const std::string &vaePath,
    ProgressInterface *progress
) : StableDiffusionModel("", cliplPath, "", t5xxlPath, diffusionPath, vaePath, progress) {
}

cv::Mat Flux1Dev::generate(const std::string &text, const int &steps) {
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
