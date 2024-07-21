#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include "ui/UploadBar.h"
#include "utils/ImgIo.h"

UploadBar::UploadBar(QWidget *parent, int type) : QWidget(parent) {
    setStyleSheet(style);

    auto *layout = new QHBoxLayout(this);

    auto *generateButton = new QPushButton(this);
    generateButton->setText(text[type]);
    generateButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(generateButton);
    layout->setAlignment(generateButton, Qt::AlignRight);
    layout->setContentsMargins(0, 9, 0, 0);

    connect(generateButton, &QPushButton::clicked, [=] {
        if (type == TYPE_DIRECTORY) {
            QString path = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
            if (!path.isEmpty()) {
                emit directorySelected(path);
            }
        } else if (type == TYPE_IMAGE) {
            QString path = QFileDialog::getOpenFileName(this, "Select Image", QDir::homePath(), "*jpg *jpeg *.png");
            if (!path.isEmpty()) {
                emit imageSelected(ImgIo::read(path.toStdString()));
            }
        }
    });
}
