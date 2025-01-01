#include "sd/QStableDiffusion.h"
#include "models/StableDiffusionV15.h"

void QStableDiffusion::start(const Sd::Params &params) {
    switch (params.model.id) {
        case Sd::MODEL_STABLE_DIFFUSION_V1_5:
            model = new StableDiffusionV15(std::string(params.path) + "/" + params.model.file, this);
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
