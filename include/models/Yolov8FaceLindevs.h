#ifndef ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H
#define ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class Yolov8FaceLindevs : OrtModel, public FaceDetectionModel {
public:
    explicit Yolov8FaceLindevs(const std::string &onnxModelPath);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale);

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};
};

#endif //ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H
