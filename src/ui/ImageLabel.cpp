#include <QFileDialog>
#include "ui/ImageLabel.h"
#include "utils/DateTime.h"
#include "utils/ImgIo.h"

ImageLabel::ImageLabel(const cv::Mat &img, const int width, QWidget *parent) : QLabel(parent), img(img) {
    auto format = img.channels() == 1 ? QImage::Format_Grayscale8 : QImage::Format_BGR888;
    QImage qimg(img.data, img.cols, img.rows, (int) img.step, format);
    setPixmap(QPixmap::fromImage(qimg).scaledToWidth(width));
    setFixedWidth(width);
    setCursor(Qt::PointingHandCursor);
}

void ImageLabel::mousePressEvent(QMouseEvent *event) {
    QLabel::mouseMoveEvent(event);

    QString path = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    if (!path.isEmpty()) {
        ImgIo::write(path.toStdString() + "/" + DateTime::current() + ".jpg", img);
    }
}
