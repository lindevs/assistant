#include "ui/CheckBox.h"

CheckBox::CheckBox(QWidget *parent) : QCheckBox(parent) {
    setStyleSheet(style);
}

void CheckBox::setText(const QString &text) {
    QCheckBox::setText(text);
}

bool CheckBox::isChecked() {
    return checkState() == Qt::Checked;
}
