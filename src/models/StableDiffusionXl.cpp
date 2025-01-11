#include "models/StableDiffusionXl.h"

StableDiffusionXl::StableDiffusionXl(
    const std::string &modelPath,
    const std::string &vaePath,
    ProgressInterface *progress
) : StableDiffusionModel(modelPath, "", "", "", vaePath, progress) {
}

cv::Mat StableDiffusionXl::generate(const std::string &text, const int &steps) {
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
