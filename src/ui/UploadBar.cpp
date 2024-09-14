#include <QLayout>
#include <QPushButton>
#include <QFileDialog>
#include "ui/UploadBar.h"
#include "utils/ImgIo.h"
#include "core/app.h"

UploadBar::UploadBar(QWidget *parent, int type) : QWidget(parent), settings(Core::ORG, Core::APP) {
    setStyleSheet(style);

    settings.beginGroup("upload");

    auto *layout = new QHBoxLayout(this);

    auto *generateButton = new QPushButton(this);
    generateButton->setText(text[type]);
    generateButton->setCursor(Qt::PointingHandCursor);

    layout->addWidget(generateButton);
    layout->setAlignment(generateButton, Qt::AlignRight);
    layout->setContentsMargins(0, 9, 0, 0);

    connect(generateButton, &QPushButton::clicked, [=] {
        QString defaultDir = settings.value("dir", QDir::homePath()).toString();

        if (type == TYPE_DIRECTORY) {
            QString path = QFileDialog::getExistingDirectory(this, "Select Directory", defaultDir);
            if (!path.isEmpty()) {
                settings.setValue("dir", path);
                emit directorySelected(path);
            }
        } else if (type == TYPE_IMAGE) {
            QString path = QFileDialog::getOpenFileName(this, "Select Image", defaultDir, "*jpg *jpeg *.png");
            if (!path.isEmpty()) {
                QFileInfo info(path);
                settings.setValue("dir", info.dir().path());
                emit imageSelected(ImgIo::read(path.toStdString()));
            }
        }
    });
}
