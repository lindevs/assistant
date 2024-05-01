#ifndef ASSISTANT_UI_IMAGE_LABEL_H
#define ASSISTANT_UI_IMAGE_LABEL_H

#include <QLabel>

class ImageLabel : public QLabel {
Q_OBJECT

public:
    explicit ImageLabel(const QImage &img, int width, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    const QImage img;
};

#endif //ASSISTANT_UI_IMAGE_LABEL_H
