#include <QLayout>
#include "ui/face/Settings.h"
#include "core/app.h"

Face::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    settings.beginGroup("face");

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

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
    params.autosave = autosave.isChecked();

    return params;
}
