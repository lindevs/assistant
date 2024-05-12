#include <QLayout>
#include "ui/SelectBox.h"

SelectBox::SelectBox(QWidget *parent) : QWidget(parent) {
    setStyleSheet(style);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    input.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(&input, &QComboBox::currentIndexChanged, this, &SelectBox::currentIndexChanged);

    layout->addWidget(&label);
    layout->addWidget(&input);
}

void SelectBox::setText(const QString &text) {
    label.setText(text);
}

void SelectBox::setCurrenctIndex(int index) {
    input.setCurrentIndex(index);
}

int SelectBox::getCurrentIndex() {
    return input.currentIndex();
}

void SelectBox::addItems(const QList<QString> &items) {
    input.addItems(items);
}
