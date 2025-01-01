#include <thread>
#if !defined(_WIN32)
#include <ggml.h>
#endif
#include "models/StableDiffusionV15.h"
#include "utils/ImgProc.h"

StableDiffusionV15::StableDiffusionV15(const std::string &modelPath, ProgressInterface *progress) {
    this->progress = progress;

#if !defined(_WIN32)
    ggml_log_set([](ggml_log_level, const char *, void *) {
    }, nullptr);
#endif

    sd_set_progress_callback([](int step, int steps, float, void *data) {
        auto self = (StableDiffusionV15 *) data;
        if (self->progress && step > 0 && self->sampleSteps == steps) {
            self->progress->changeStep(step);
        }
    }, this);

    sdCtx = new_sd_ctx(
        modelPath.c_str(), "", "", "", "", "", "", "", "", "", "",
        true, false, false, (int) std::thread::hardware_concurrency(),
        SD_TYPE_COUNT, CUDA_RNG, DEFAULT, false, false, false, false
    );
}

StableDiffusionV15::~StableDiffusionV15() {
    free_sd_ctx(sdCtx);
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

    cv::Mat img((int) result[0].height, (int) result[0].width, CV_8UC3, result[0].data);
    ImgProc::rgb2bgr(img, img);

    free(result);

    return img;
}
