#include "models/YoloFaceV2.h"
#include "utils/ImgProc.h"

YoloFaceV2::YoloFaceV2(const std::string &onnxModelPath, Core::Backend backend) : OrtModel(onnxModelPath, backend) {
}

std::vector<Face::Detection> YoloFaceV2::detect(const cv::Mat &input) {
    cv::Mat blob;
    XyScale xyScale;
    preprocess(input, blob, xyScale);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 1);

    int64_t rows = outputDims[0][1];
    int64_t dimensions = outputDims[0][2];

    std::vector<float> confidences;
    std::vector<cv::Rect2f> boxes;

    auto *data = outputTensors[0].GetTensorData<float>();
    for (int i = 0; i < rows; ++i) {
        float objScore = *(data + 4);
        if (objScore < modelScoreThreshold) {
            data += dimensions;

            continue;
        }

        float classScore = *(data + 5) * objScore;
        if (classScore > modelScoreThreshold) {
            confidences.emplace_back(classScore);

            const float cx = *data;
            const float cy = *(data + 1);
            const float w = *(data + 2);
            const float h = *(data + 3);

            boxes.emplace_back(
                (cx - xyScale.x - 0.5f * w) * xyScale.scale,
                (cy - xyScale.y - 0.5f * h) * xyScale.scale,
                w * xyScale.scale,
                h * xyScale.scale
            );
        }

        data += dimensions;
    }

    std::vector<int> indices;
    ImgProc::nms(boxes, confidences, modelNmsThreshold, indices);

    std::vector<Face::Detection> detections{};
    for (int i: indices) {
        detections.emplace_back(
            confidences[i],
            cv::Rect(
                (int) std::nearbyint(boxes[i].x),
                (int) std::nearbyint(boxes[i].y),
                (int) std::nearbyint(boxes[i].width),
                (int) std::nearbyint(boxes[i].height)
            )
        );
    }

    return detections;
}

void YoloFaceV2::preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale) {
    ImgProc::letterbox(input, blob, modelInputShape, xyScale);
    ImgProc::hwcToNchw(blob, blob);
    ImgProc::scale(blob);
}
