#include "dedup/QImageDeduplication.h"
#include "models/MobileNetV3Dedup.h"

void QImageDeduplication::start(const Dedup::Params &params) {
    switch (params.model.id) {
        case Dedup::MODEL_MOBILE_NET_V3_SMALL_DEDUP:
        default:
            model = new MobileNetV3Dedup(std::string(params.path) + "/" + params.model.file);
    }
    deduplication = new ImageDeduplication(model);
}

void QImageDeduplication::stop() {
    delete deduplication;
    deduplication = nullptr;
    delete model;
    model = nullptr;
}

void QImageDeduplication::findDuplicates(const QString &path) {
    emit found(deduplication->findDuplicates(path.toStdString()));
}
