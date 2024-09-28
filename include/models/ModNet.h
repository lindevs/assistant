#ifndef ASSISTANT_MODELS_MODNET_H
#define ASSISTANT_MODELS_MODNET_H

#include "models/OrtModel.h"
#include "models/BackgroundMattingModel.h"

class ModNet : OrtModel, public BackgroundMattingModel {
public:
    explicit ModNet(const std::string &onnxModelPath);

    cv::Mat generate(const cv::Mat &input) override;

private:
    void preprocess(const cv::Mat &input, cv::Mat &blob, cv::Size &dstSize);

    int refSize{512};
    const cv::Scalar mean{0.5};
    const cv::Scalar std{0.5};
};

#endif //ASSISTANT_MODELS_MODNET_H
