#include <QLayout>
#include "ui/SelectBox.h"

SelectBox::SelectBox(QWidget *parent) : QWidget(parent) {
    setStyleSheet(style);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    input.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->addWidget(&label);
    layout->addWidget(&input);
}

void SelectBox::setText(const QString &text) {
    label.setText(text);
}

int SelectBox::getValueIndex() {
    return input.currentIndex();
}

void SelectBox::addItems(const QList<QString> &items) {
    input.addItems(items);
}
