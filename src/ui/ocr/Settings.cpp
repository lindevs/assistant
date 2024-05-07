#include <QLayout>
#include "ui/ocr/Settings.h"

Ocr::Settings::Settings(QWidget *parent) : QGroupBox(parent) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    language.setText("Language");
    language.addItems(languages);
    layout->addWidget(&language);

    layout->setAlignment(Qt::AlignTop);
}

Ocr::Params Ocr::Settings::getParams() {
    Params params;
    params.language = codes[language.getValueIndex()];

    return params;
}
