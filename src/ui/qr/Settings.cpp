#include <QLayout>
#include <QCheckBox>
#include "ui/qr/Settings.h"
#include "core/app.h"

Qr::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    settings.beginGroup("qr");

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    width.setText("Width");
    width.setMinMaxValue(29, 1024);
    width.setValue(settings.value("width", 512).toInt());
    connect(&width, &Slider::valueChanged, [=] (int value) {
        settings.setValue("width", value);
    });
    layout->addWidget(&width);

    height.setText("Height");
    height.setMinMaxValue(29, 1024);
    height.setValue(settings.value("height", 512).toInt());
    connect(&height, &Slider::valueChanged, [=] (int value) {
        settings.setValue("height", value);
    });
    layout->addWidget(&height);

    autosave.setText("Save output automatically");
    autosave.setChecked(settings.value("autosave", false).toBool());
    connect(&autosave, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("autosave", checked);
    });
    layout->addWidget(&autosave);

    layout->setAlignment(Qt::AlignTop);
}

Qr::Params Qr::Settings::getParams() {
    Params params;
    params.width = width.getValue();
    params.height = height.getValue();
    params.autosave = autosave.isChecked();

    return params;
}
