#include "models/Flux1Schnell.h"

Flux1Schnell::Flux1Schnell(
    const std::string &cliplPath,
    const std::string &t5xxlPath,
    const std::string &diffusionPath,
    const std::string &vaePath,
    ProgressInterface *progress
) : StableDiffusionModel("", cliplPath, "", t5xxlPath, diffusionPath, vaePath, progress) {
}

cv::Mat Flux1Schnell::generate(const std::string &text, const int &steps) {
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
