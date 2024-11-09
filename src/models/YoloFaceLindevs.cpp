#include "models/YoloFaceLindevs.h"
#include "utils/ImgProc.h"

YoloFaceLindevs::YoloFaceLindevs(const std::string &onnxModelPath) : OrtModel(onnxModelPath) {
}

std::vector<Face::Detection> YoloFaceLindevs::detect(const cv::Mat &input) {
    cv::Mat blob;
    XyScale xyScale;
    preprocess(input, blob, xyScale);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 1);

    int64_t rows = outputDims[0][2];
    int64_t dimensions = outputDims[0][1];

    std::vector<float> confidences;
    std::vector<cv::Rect2f> boxes;

    auto *data = outputTensors[0].GetTensorData<float>();
    for (int i = 0; i < rows; ++i) {
        float maxClassScore = 0;
        for (int j = 4; j < dimensions; ++j) {
            float classScore = *(data + j * rows);
            if (classScore > maxClassScore) {
                maxClassScore = classScore;
            }
        }

        if (maxClassScore > modelScoreThreshold) {
            confidences.emplace_back(maxClassScore);

            const float cx = *data;
            const float cy = *(data + rows);
            const float w = *(data + rows * 2);
            const float h = *(data + rows * 3);

            boxes.emplace_back(
                (cx - xyScale.x - 0.5f * w) * xyScale.scale,
                (cy - xyScale.y - 0.5f * h) * xyScale.scale,
                w * xyScale.scale,
                h * xyScale.scale
            );
        }

        data++;
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

void YoloFaceLindevs::preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale) {
    ImgProc::letterbox(input, blob, modelInputShape, xyScale);
    ImgProc::hwcToNchw(blob, blob);
    ImgProc::scale(blob);
}
