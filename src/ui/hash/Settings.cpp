#include <QLayout>
#include "ui/hash/Settings.h"
#include "core/app.h"

Hash::Settings::Settings(QWidget *parent) : QGroupBox(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet("QGroupBox {border: 1px solid #ccc;border-radius: 4px;}");

    settings.beginGroup("hash");

    auto *layout = new QVBoxLayout(this);

    algorithm.setText("Algorithm");
    algorithm.addItems(algorithms);
    algorithm.setCurrenctIndex(settings.value("algorithm", 0).toInt());
    connect(&algorithm, &SelectBox::currentIndexChanged, [=] (int index) {
        settings.setValue("algorithm", index);
    });
    layout->addWidget(&algorithm);

    layout->setAlignment(Qt::AlignTop);
}

Hash::Params Hash::Settings::getParams() {
    Params params;
    params.algorithm.id = algorithm.getCurrentIndex();

    return params;
}
