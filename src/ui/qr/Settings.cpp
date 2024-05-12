#include <QLayout>
#include <QCheckBox>
#include "ui/qr/Settings.h"

Qr::Settings::Settings(QWidget *parent) : QGroupBox(parent) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    width.setText("Width");
    width.setMinMaxValue(29, 1024);
    width.setValue(512);
    layout->addWidget(&width);

    height.setText("Height");
    height.setMinMaxValue(29, 1024);
    height.setValue(512);
    layout->addWidget(&height);

    autosave.setText("Save output automatically");
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
