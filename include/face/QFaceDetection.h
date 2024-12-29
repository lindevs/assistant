#ifndef ASSISTANT_FACE_QFACE_DETECTION_H
#define ASSISTANT_FACE_QFACE_DETECTION_H

#include <QObject>
#include "models/FaceDetectionModel.h"

class QFaceDetection : public QObject {
Q_OBJECT

public:
    void start(const Face::Params &params);

    void stop();

    void detect(const cv::Mat &img);

signals:

    void detected(const std::vector<Face::Detection> &detections);

private:
    FaceDetectionModel *model = nullptr;
};

#endif //ASSISTANT_FACE_QFACE_DETECTION_H
