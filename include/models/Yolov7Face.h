#ifndef ASSISTANT_MODELS_YOLOV7_FACE_H
#define ASSISTANT_MODELS_YOLOV7_FACE_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class Yolov7Face : OrtModel, public FaceDetectionModel {
public:
    explicit Yolov7Face(const std::string &onnxModelPath);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale);

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};
};

#endif //ASSISTANT_MODELS_YOLOV7_FACE_H
