#include "models/StableDiffusion35Large.h"

StableDiffusion35Large::StableDiffusion35Large(
    const std::string &modelPath,
    const std::string &cliplPath,
    const std::string &clipgPath,
    const std::string &t5xxlPath,
    ProgressInterface *progress
) : StableDiffusionModel(modelPath, cliplPath, clipgPath, t5xxlPath, progress) {
}

cv::Mat StableDiffusion35Large::generate(const std::string &text, const int &steps) {
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
