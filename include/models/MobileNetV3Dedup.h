#ifndef ASSISTANT_MODELS_MOBILE_NET_V3_DEDUP_H
#define ASSISTANT_MODELS_MOBILE_NET_V3_DEDUP_H

#include "models/OrtModel.h"
#include "models/DeduplicationModel.h"

class MobileNetV3Dedup : OrtModel, public DeduplicationModel {
public:
    explicit MobileNetV3Dedup(const std::string &onnxModelPath);

    cv::Mat encode(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob);

    const float resizeScale{0.875f};
    const float mean[3]{0.406f, 0.456f, 0.485f};
    const float std[3]{0.225f, 0.224f, 0.229f};
};

#endif //ASSISTANT_MODELS_MOBILE_NET_V3_DEDUP_H
