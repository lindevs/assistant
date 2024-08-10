#include "models/UltraFace.h"
#include "utils/ImgProc.h"

UltraFace::UltraFace(const std::string &onnxModelPath) : OrtModel(onnxModelPath) {
}

std::vector<Face::Detection> UltraFace::detect(const cv::Mat &input) {
    cv::Mat blob;
    preprocess(input, blob);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 2);

    int64_t rows = outputDims[0][1];

    std::vector<float> confidences;
    std::vector<cv::Rect2f> boxes;

    const auto *classScores = outputTensors[0].GetTensorData<float>();
    const auto *classBoxes = outputTensors[1].GetTensorData<float>();
    for (int i = 0; i < rows; ++i) {
        float confidence = *(classScores + 1);
        if (confidence > modelScoreThreshold) {
            confidences.emplace_back(confidence);

            const float xmin = *classBoxes;
            const float ymin = *(classBoxes + 1);
            const float xmax = *(classBoxes + 2);
            const float ymax = *(classBoxes + 3);

            boxes.emplace_back(
                xmin * (float) input.cols,
                ymin * (float) input.rows,
                (xmax - xmin) * (float) input.cols,
                (ymax - ymin) * (float) input.rows
            );
        }

        classScores += 2;
        classBoxes += 4;
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

void UltraFace::preprocess(const cv::Mat &input, cv::Mat &blob) {
    ImgProc::resize(input, blob, modelInputShape);
    ImgProc::hwcToNchw(blob, blob);
    ImgProc::convertToFloat(blob);
    ImgProc::normalize(blob, mean, std);
}
