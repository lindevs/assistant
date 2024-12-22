#include "models/RetinaFace.h"
#include "utils/ImgProc.h"

RetinaFace::RetinaFace(const std::string &onnxModelPath, Core::Backend backend) : OrtModel(onnxModelPath, backend) {
    generateAnchors();
}

std::vector<Face::Detection> RetinaFace::detect(const cv::Mat &input) {
    cv::Mat blob;
    XyScale xyScale;
    preprocess(input, blob, xyScale);

    Ort::Value inputTensor = Ort::Value::CreateTensor<float>(
        memoryInfo, (float *) blob.data, inputTensorSize, inputDims.data(), inputDims.size()
    );

    std::vector<Ort::Value> outputTensors = session.Run(runOptions, &inputName, &inputTensor, 1, outputNames.data(), 3);

    int64_t rows = outputDims[0][1];

    auto inputW = (float) modelInputShape.width;
    auto inputH = (float) modelInputShape.height;

    std::vector<float> confidences;
    std::vector<cv::Rect2f> boxes;
    std::vector<std::array<Face::Point, 5>> pts;

    auto *classBoxes = outputTensors[0].GetTensorData<float>();
    auto *classScores = outputTensors[1].GetTensorData<float>();
    auto *keypoints = outputTensors[2].GetTensorData<float>();
    for (int i = 0; i < rows; ++i) {
        float confidence = *(classScores + 1);
        if (confidence > modelScoreThreshold) {
            confidences.emplace_back(confidence);

            const float cx = (anchors[i][0] + *classBoxes * variance[0] * anchors[i][2]) * inputW;
            const float cy = (anchors[i][1] + *(classBoxes + 1) * variance[0] * anchors[i][3]) * inputH;
            const float w = anchors[i][2] * std::exp(*(classBoxes + 2) * variance[1]) * inputW;
            const float h = anchors[i][3] * std::exp(*(classBoxes + 3) * variance[1]) * inputH;

            boxes.emplace_back(
                (cx - xyScale.x - 0.5f * w) * xyScale.scale,
                (cy - xyScale.y - 0.5f * h) * xyScale.scale,
                w * xyScale.scale,
                h * xyScale.scale
            );

            std::array<Face::Point, 5> pt{
                {
                    {
                        cv::Point(
                            int((((anchors[i][0] + *keypoints * variance[0] * anchors[i][2]) * inputW) - xyScale.x) *
                                xyScale.scale),
                            int((((anchors[i][1] + *(keypoints + 1) * variance[0] * anchors[i][3]) * inputH) -
                                 xyScale.y) * xyScale.scale)
                        ),
                    },
                    {
                        cv::Point(
                            int((((anchors[i][0] + *(keypoints + 2) * variance[0] * anchors[i][2]) * inputW) -
                                 xyScale.x) * xyScale.scale),
                            int((((anchors[i][1] + *(keypoints + 3) * variance[0] * anchors[i][3]) * inputH) -
                                 xyScale.y) * xyScale.scale)
                        ),
                    },
                    {
                        cv::Point(
                            int((((anchors[i][0] + *(keypoints + 4) * variance[0] * anchors[i][2]) * inputW) -
                                 xyScale.x) * xyScale.scale),
                            int((((anchors[i][1] + *(keypoints + 5) * variance[0] * anchors[i][3]) * inputH) -
                                 xyScale.y) * xyScale.scale)
                        ),
                    },
                    {
                        cv::Point(
                            int((((anchors[i][0] + *(keypoints + 6) * variance[0] * anchors[i][2]) * inputW) -
                                 xyScale.x) * xyScale.scale),
                            int((((anchors[i][1] + *(keypoints + 7) * variance[0] * anchors[i][3]) * inputH) -
                                 xyScale.y) * xyScale.scale)
                        ),
                    },
                    {
                        cv::Point(
                            int((((anchors[i][0] + *(keypoints + 8) * variance[0] * anchors[i][2]) * inputW) -
                                 xyScale.x) * xyScale.scale),
                            int((((anchors[i][1] + *(keypoints + 9) * variance[0] * anchors[i][3]) * inputH) -
                                 xyScale.y) * xyScale.scale)
                        ),
                    },
                }
            };

            pts.emplace_back(pt);
        }

        classScores += 2;
        classBoxes += 4;
        keypoints += 10;
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
            ),
            pts[i][0],
            pts[i][1],
            pts[i][2],
            pts[i][3],
            pts[i][4]
        );
    }

    return detections;
}

void RetinaFace::preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale) {
    ImgProc::letterbox(input, blob, modelInputShape, xyScale);
    ImgProc::convertToFloat(blob);
    ImgProc::normalize(blob, mean);
    ImgProc::hwcToNchw(blob, blob);
}

void RetinaFace::generateAnchors() {
    int featureMaps[3][2];
    for (int i = 0; i < 3; ++i) {
        featureMaps[i][0] = (int) std::ceil((float) modelInputShape.height / (float) steps[i]);
        featureMaps[i][1] = (int) std::ceil((float) modelInputShape.width / (float) steps[i]);
    }

    for (int k = 0; k < 3; ++k) {
        const int fh = featureMaps[k][0];
        const int fw = featureMaps[k][1];

        for (int i = 0; i < fh; ++i) {
            for (int j = 0; j < fw; ++j) {
                for (auto minSize: minSizes[k]) {
                    std::array<float, 4> anchor{
                        ((float) j + 0.5f) * (float) steps[k] / (float) modelInputShape.width,
                        ((float) i + 0.5f) * (float) steps[k] / (float) modelInputShape.height,
                        (float) minSize / (float) modelInputShape.width,
                        (float) minSize / (float) modelInputShape.height,
                    };
                    anchors.emplace_back(anchor);
                }
            }
        }
    }
}
