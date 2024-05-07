#include <QLayout>
#include "ui/MessageDialog.h"

MessageDialog::MessageDialog(const QString &title, QWidget *parent) : QDialog(parent) {
    setStyleSheet(style);
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 30, 20, 30);
    setLayout(layout);
    setWindowTitle(title);
    setModal(true);

    label.setCursor(Qt::IBeamCursor);
    label.setTextFormat(Qt::RichText);
    label.setTextInteractionFlags(Qt::TextBrowserInteraction);
    label.setOpenExternalLinks(true);

    layout->addWidget(&label);
}

void MessageDialog::setText(const QString &text) {
    label.setText(text);
}
