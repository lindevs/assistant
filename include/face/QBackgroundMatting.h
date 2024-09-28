#ifndef ASSISTANT_FACE_QBACKGROUND_MATTING_H
#define ASSISTANT_FACE_QBACKGROUND_MATTING_H

#include <QObject>
#include <opencv2/core/mat.hpp>
#include "models/BackgroundMattingModel.h"

class QBackgroundMatting : public QObject {
Q_OBJECT

public:
    void start(const Face::Params &params);

    void stop();

    void generate(const cv::Mat &img);

signals:

    void generated(const cv::Mat &matte);

private:
    BackgroundMattingModel *model;
};

#endif //ASSISTANT_FACE_QBACKGROUND_MATTING_H
