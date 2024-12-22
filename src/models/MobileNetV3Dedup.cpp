#include "models/MobileNetV3Dedup.h"
#include "utils/ImgProc.h"
#include "utils/ImgResize.h"

MobileNetV3Dedup::MobileNetV3Dedup(const std::string &onnxModelPath, Core::Backend backend)
    : OrtModel(onnxModelPath, backend) {
}

cv::Mat MobileNetV3Dedup::encode(const cv::Mat &input) {
    cv::Mat blob;
    preprocess(input, blob);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 1);

    cv::Mat output(1, (int) outputDims[0][1], CV_32FC1, outputTensors[0].GetTensorMutableData<float>());

    return output.clone();
}

void MobileNetV3Dedup::preprocess(const cv::Mat &input, cv::Mat &blob) {
    blob = ImgResize::resize(input, ImgProc::scale(modelInputShape, resizeScale), ImgResize::INTERPOLATION_BILINEAR);
    ImgProc::centerCrop(blob, modelInputShape);
    ImgProc::scaleAndNormalize(blob, mean, std);
    ImgProc::hwcToNchw(blob, blob);
}
