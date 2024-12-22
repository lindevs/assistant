#include "face/QBackgroundMatting.h"
#include "models/ModNet.h"

void QBackgroundMatting::start(const Face::Params &params) {
    switch (params.mattingModel.id) {
        case Matting::MODEL_MODNET_PHOTOGRAPHIC:
            model = new ModNet(std::string(params.path) + "/" + params.mattingModel.file, params.backend);
            break;
        default:
            model = nullptr;
    }
}

void QBackgroundMatting::stop() {
    delete model;
    model = nullptr;
}

void QBackgroundMatting::generate(const cv::Mat &img) {
    emit generated(model->generate(img));
}
