#ifndef ASSISTANT_MODELS_YOLO_FACE_V2_H
#define ASSISTANT_MODELS_YOLO_FACE_V2_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class YoloFaceV2 : OrtModel, public FaceDetectionModel {
public:
    explicit YoloFaceV2(const std::string &onnxModelPath, Core::Backend backend = Core::Backend::CPU);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale);

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};
};

#endif //ASSISTANT_MODELS_YOLO_FACE_V2_H
