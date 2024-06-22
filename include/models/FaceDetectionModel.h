#ifndef ASSISTANT_MODELS_FACE_DETECTION_MODEL_H
#define ASSISTANT_MODELS_FACE_DETECTION_MODEL_H

#include "core/structures.h"

class FaceDetectionModel {
public:
    virtual ~FaceDetectionModel() = default;

    virtual std::vector<Face::Detection> detect(const cv::Mat &input) = 0;
};

#endif //ASSISTANT_MODELS_FACE_DETECTION_MODEL_H
