#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include "ui/UploadBar.h"
#include "utils/ImageIo.h"

UploadBar::UploadBar(QWidget *parent) : QWidget(parent) {
    setStyleSheet(style);

    auto *layout = new QHBoxLayout(this);

    auto *generateButton = new QPushButton(this);
    generateButton->setText("Select Image...");
    generateButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(generateButton);
    layout->setAlignment(generateButton, Qt::AlignRight);
    layout->setContentsMargins(0, 9, 0, 0);

    connect(generateButton, &QPushButton::clicked, [=] {
        QString path = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "*jpg *jpeg *.png");
        if (!path.isEmpty()) {
            emit imageSelected(ImageIo::read(path.toStdString()));
        }
    });
}
