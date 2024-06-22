#ifndef ASSISTANT_MODELS_LIBFACEDETECTION_H
#define ASSISTANT_MODELS_LIBFACEDETECTION_H

#include <opencv2/core/mat.hpp>
#include "models/FaceDetectionModel.h"

class Libfacedetection : public FaceDetectionModel {
public:
    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    int modelScoreThreshold{80};
};

#endif //ASSISTANT_MODELS_LIBFACEDETECTION_H
