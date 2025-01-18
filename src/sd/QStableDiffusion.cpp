#include "core/structures.h"
#include "sd/QStableDiffusion.h"
#include "models/StableDiffusionV15.h"
#include "models/StableDiffusionXl.h"
#include "models/StableDiffusion3Medium.h"
#include "models/StableDiffusion35Medium.h"
#include "models/StableDiffusion35Large.h"

void QStableDiffusion::start(const Sd::Params &params) {
    std::string path = std::string(params.path) + "/";
    switch (params.model.id) {
        case Sd::MODEL_STABLE_DIFFUSION_V1_5:
            model = new StableDiffusionV15(path + params.model.files[0], this);
            break;
        case Sd::MODEL_STABLE_DIFFUSION_XL:
            model = new StableDiffusionXl(path + params.model.files[0], path + params.model.files[1], this);
        break;
        case Sd::MODEL_STABLE_DIFFUSION_3_MEDIUM:
            model = new StableDiffusion3Medium(path + params.model.files[0], this);
        break;
        case Sd::MODEL_STABLE_DIFFUSION_3_5_MEDIUM:
            model = new StableDiffusion35Medium(
                path + params.model.files[0],
                path + params.model.files[1],
                path + params.model.files[2],
                path + params.model.files[3],
                this
            );
            break;
        case Sd::MODEL_STABLE_DIFFUSION_3_5_LARGE:
            model = new StableDiffusion35Large(
                path + params.model.files[0],
                path + params.model.files[1],
                path + params.model.files[2],
                path + params.model.files[3],
                this
            );
        break;
        default:
            model = nullptr;
    }
}

void QStableDiffusion::stop() {
    delete model;
    model = nullptr;
}

void QStableDiffusion::changeStep(const int &step) {
    emit stepChanged(step);
}

void QStableDiffusion::generate(const QString &text, const int &steps) {
    emit generated(model->generate(text.toStdString(), steps));
}
