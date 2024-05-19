#include <QLayout>
#include "ui/face/Settings.h"
#include "core/app.h"

Face::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    settings.beginGroup("face");

    auto *layout = new QVBoxLayout(this);

    blur.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    blur.setText("Blur faces");
    blur.setChecked(settings.value("blur", false).toBool());
    connect(&blur, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("blur", checked);
    });
    layout->addWidget(&blur);

    autosave.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    autosave.setText("Save output automatically");
    autosave.setChecked(settings.value("autosave", false).toBool());
    connect(&autosave, &QCheckBox::clicked, [=] (bool checked) {
        settings.setValue("autosave", checked);
    });
    layout->addWidget(&autosave);

    layout->setAlignment(Qt::AlignTop);
}

Face::Params Face::Settings::getParams() {
    Params params;
    params.blur = blur.isChecked();
    params.autosave = autosave.isChecked();

    return params;
}
