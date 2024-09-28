#include "models/ModNet.h"
#include "utils/ImgProc.h"

ModNet::ModNet(const std::string &onnxModelPath) : OrtModel(onnxModelPath) {
}

cv::Mat ModNet::generate(const cv::Mat &input) {
    cv::Mat blob;
    cv::Size dstSize;
    preprocess(input, blob, dstSize);

    inputDims[2] = dstSize.height;
    inputDims[3] = dstSize.width;
    inputTensorSize = blob.total();

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 1);

    cv::Mat matte(dstSize, CV_32FC1, outputTensors[0].GetTensorMutableData<float>());
    ImgProc::resizeArea(matte, matte, input.size());

    return matte;
}

void ModNet::preprocess(const cv::Mat &input, cv::Mat &blob, cv::Size &dstSize) {
    dstSize = ImgProc::computeSizeForResize(input.size(), refSize);
    ImgProc::resizeArea(input, blob, dstSize);
    ImgProc::hwcToNchw(blob, blob);
    ImgProc::scale(blob);
    ImgProc::normalize(blob, mean, std);
}
