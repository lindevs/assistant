#ifndef ASSISTANT_MODELS_RETINA_FACE_H
#define ASSISTANT_MODELS_RETINA_FACE_H

#include "models/OrtModel.h"
#include "models/FaceDetectionModel.h"

class RetinaFace : OrtModel, public FaceDetectionModel {
public:
    explicit RetinaFace(const std::string &onnxModelPath, Core::Backend backend = Core::Backend::CPU);

    std::vector<Face::Detection> detect(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale);

    void generateAnchors();

    float modelScoreThreshold{0.80f};
    float modelNmsThreshold{0.70f};

    const cv::Scalar mean{104, 117, 123};
    const float variance[2]{0.1f, 0.2f};
    const int steps[3]{8, 16, 32};
    const int minSizes[3][2]{
        {16,  32},
        {64,  128},
        {256, 512},
    };

    std::vector<std::array<float, 4>> anchors;
};

#endif //ASSISTANT_MODELS_RETINA_FACE_H
