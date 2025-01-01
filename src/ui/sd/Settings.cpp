#include <QLayout>
#include "ui/sd/Settings.h"
#include "core/app.h"

Sd::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet(style);

    settings.beginGroup("sd");

    auto *layout = new QVBoxLayout(this);

    model.setText("Model");
    model.addItems(models);
    model.setCurrenctIndex(settings.value("model", 0).toInt());
    connect(&model, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("model", index);
    });
    layout->addWidget(&model);

    steps.setText("Steps");
    steps.setMinMaxValue(1, 100);
    steps.setValue(settings.value("steps", 20).toInt());
    connect(&steps, &Slider::valueChanged, [=] (int value) {
        settings.setValue("steps", value);
    });
    layout->addWidget(&steps);

    autosave.setText("Save output automatically");
    autosave.setChecked(settings.value("autosave", false).toBool());
    connect(&autosave, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("autosave", checked);
    });
    layout->addWidget(&autosave);

    layout->setAlignment(Qt::AlignTop);
}

Sd::Params Sd::Settings::getParams() {
    Params params;
    params.model.id = model.getCurrentIndex();
    params.model.file = MODEL_FILES[model.getCurrentIndex()];
    params.model.url = MODEL_URLS[model.getCurrentIndex()];
    params.steps = steps.getValue();
    params.autosave = autosave.isChecked();

    return params;
}
