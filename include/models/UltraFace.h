#ifndef ASSISTANT_MODELS_ULTRA_FACE_H
#define ASSISTANT_MODELS_ULTRA_FACE_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class UltraFace : OrtModel, public FaceDetectionModel {
public:
    explicit UltraFace(const std::string &onnxModelPath);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob);

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};
    const cv::Scalar mean{127.0f};
    const cv::Scalar std{128.0f};
};

#endif //ASSISTANT_MODELS_ULTRA_FACE_H
