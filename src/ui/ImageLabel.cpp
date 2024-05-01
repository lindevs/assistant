#include <QFileDialog>
#include "ui/ImageLabel.h"

ImageLabel::ImageLabel(const QImage &img, const int width, QWidget *parent) : QLabel(parent), img(img) {
    setPixmap(QPixmap::fromImage(img).scaledToWidth(width));
    setFixedWidth(width);
    setCursor(Qt::PointingHandCursor);
}

void ImageLabel::mousePressEvent(QMouseEvent *event) {
    QLabel::mouseMoveEvent(event);

    QString path = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath());
    if (!path.isEmpty()) {
        img.save(path + "/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".jpg");
    }
}
