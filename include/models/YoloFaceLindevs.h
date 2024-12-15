#ifndef ASSISTANT_MODELS_YOLO_FACE_LINDEVS_H
#define ASSISTANT_MODELS_YOLO_FACE_LINDEVS_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class YoloFaceLindevs : OrtModel, public FaceDetectionModel {
public:
    explicit YoloFaceLindevs(const std::string &onnxModelPath);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale);

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};
};

#endif //ASSISTANT_MODELS_YOLO_FACE_LINDEVS_H