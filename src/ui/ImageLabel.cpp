#include <QFileDialog>
#include <opencv2/imgcodecs.hpp>
#include "ui/ImageLabel.h"

ImageLabel::ImageLabel(const cv::Mat &img, const int width, QWidget *parent) : QLabel(parent), img(img) {
    auto format = img.channels() == 1 ? QImage::Format_Grayscale8 : QImage::Format_BGR888;
    QImage qimg(img.data, img.cols, img.rows, (int) img.step, format);
    setPixmap(QPixmap::fromImage(qimg).scaledToWidth(width));
    setFixedWidth(width);
    setCursor(Qt::PointingHandCursor);
}

void ImageLabel::mousePressEvent(QMouseEvent *event) {
    QLabel::mouseMoveEvent(event);

    QString path = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath());
    if (!path.isEmpty()) {
        cv::imwrite((path + "/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmss") + ".jpg").toStdString(), img);
    }
}
