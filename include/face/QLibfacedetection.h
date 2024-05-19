#ifndef ASSISTANT_FACE_QLIBFACEDETECTION_H
#define ASSISTANT_FACE_QLIBFACEDETECTION_H

#include <QObject>
#include <opencv2/core/mat.hpp>
#include "face/Libfacedetection.h"

class QLibfacedetection : public QObject {
Q_OBJECT

public:
    void detect(const cv::Mat &img);

signals:

    void detected(const std::vector<Face::Detection> &detections, const cv::Mat &img);

private:
    Libfacedetection libfacedetection;
};

#endif //ASSISTANT_FACE_QLIBFACEDETECTION_H
