#include <QLayout>
#include "ui/Line.h"
#include "ui/dedup/Settings.h"
#include "core/app.h"

Dedup::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet(style);

    settings.beginGroup("dedup");

    auto *layout = new QVBoxLayout(this);

    backend.setCurrenctIndex(settings.value("backend", 0).toInt());
    connect(&backend, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("backend", index);
    });
    layout->addWidget(&backend);

    layout->addWidget(new Line());

    model.setText("Model");
    model.addItems(models);
    model.setCurrenctIndex(settings.value("model", 0).toInt());
    connect(&model, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("model", index);
    });
    layout->addWidget(&model);

    layout->setAlignment(Qt::AlignTop);
}

Dedup::Params Dedup::Settings::getParams() {
    Params params;
    params.model.id = model.getCurrentIndex();
    params.model.file = MODEL_FILES[model.getCurrentIndex()];
    params.model.url = MODEL_URLS[model.getCurrentIndex()];
    params.backend = backend.getCurrentBackend();

    return params;
}
