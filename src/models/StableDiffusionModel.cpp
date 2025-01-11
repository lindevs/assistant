#include <thread>
#if !defined(_WIN32)
#include <ggml.h>
#endif
#include "models/StableDiffusionModel.h"
#include "utils/ImgProc.h"

StableDiffusionModel::StableDiffusionModel(
        const std::string &modelPath,
        const std::string &cliplPath,
        const std::string &clipgPath,
        const std::string &t5xxlPath,
        const std::string &vaePath,
        ProgressInterface *progress
) {
    this->progress = progress;

#if !defined(_WIN32)
    ggml_log_set([](ggml_log_level, const char *, void *) {
    }, nullptr);
#endif

    sd_set_progress_callback([](int step, int steps, float, void *data) {
        auto self = (StableDiffusionModel *) data;
        if (self->progress && step > 0 && self->sampleSteps == steps) {
            self->progress->changeStep(step);
        }
    }, this);

    sdCtx = new_sd_ctx(
        modelPath.c_str(), cliplPath.c_str(), clipgPath.c_str(), t5xxlPath.c_str(), "", vaePath.c_str(),
        "", "", "", "", "",
        true, false, false, (int) std::thread::hardware_concurrency(),
        SD_TYPE_COUNT, CUDA_RNG, DEFAULT, false, false, false, false
    );
}

StableDiffusionModel::~StableDiffusionModel() {
    free_sd_ctx(sdCtx);
}

cv::Mat StableDiffusionModel::createImage(sd_image_t *result) {
    cv::Mat img((int) result[0].height, (int) result[0].width, CV_8UC3, result[0].data);
    ImgProc::rgb2bgr(img, img);
    free(result);

    return img;
}
