#include <QFileDialog>
#include "ui/ImageLabel.h"
#include "utils/DateTime.h"
#include "utils/ImgIo.h"
#include "utils/ImgProc.h"

ImageLabel::ImageLabel(const cv::Mat &img, const int width, QWidget *parent) : QLabel(parent), img(img) {
    setStyleSheet(style);
    cv::Mat cimg = img;

    auto format = QImage::Format_BGR888;
    if (img.channels() == 1) {
        format = QImage::Format_Grayscale8;
    } else if (img.channels() == 4) {
        cimg = img.clone();
        ImgProc::bgra2rgba(cimg, cimg);
        format = QImage::Format_RGBA8888;
    }

    QImage qimg(cimg.data, cimg.cols, cimg.rows, (int) cimg.step, format);
    if (cimg.cols > width) {
        setPixmap(QPixmap::fromImage(qimg).scaledToWidth(width));
        setFixedWidth(width);
    } else {
        setPixmap(QPixmap::fromImage(qimg));
        setFixedWidth(cimg.cols);
    }
    setCursor(Qt::PointingHandCursor);
}

void ImageLabel::mousePressEvent(QMouseEvent *event) {
    QLabel::mouseMoveEvent(event);

    QString path = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    if (!path.isEmpty()) {
        auto extension = img.channels() == 4 ? ".png" : ".jpg";
        ImgIo::write(path.toStdString() + "/" + DateTime::current() + extension, img);
    }
}
