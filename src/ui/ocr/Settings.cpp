#include <QLayout>
#include "ui/ocr/Settings.h"
#include "core/app.h"

Ocr::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet(style);

    settings.beginGroup("ocr");

    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(20);

    language.setText("Language");
    language.addItems(languages);
    language.setCurrenctIndex(settings.value("language", 0).toInt());
    connect(&language, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("language", index);
    });
    layout->addWidget(&language);

    layout->setAlignment(Qt::AlignTop);
}

Ocr::Params Ocr::Settings::getParams() {
    Params params;
    params.language = codes[language.getCurrentIndex()];

    return params;
}
