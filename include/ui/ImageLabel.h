#ifndef ASSISTANT_UI_IMAGE_LABEL_H
#define ASSISTANT_UI_IMAGE_LABEL_H

#include <QLabel>
#include <opencv2/core/mat.hpp>

class ImageLabel : public QLabel {
Q_OBJECT

public:
    explicit ImageLabel(const cv::Mat &img, int width, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    const cv::Mat img;

    QString style = R"(
        QFileDialog QWidget {
            font-size: 12px;
        }
    )";
};

#endif //ASSISTANT_UI_IMAGE_LABEL_H
