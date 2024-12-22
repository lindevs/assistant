#include "models/Yolov7Face.h"
#include "utils/ImgProc.h"

Yolov7Face::Yolov7Face(const std::string &onnxModelPath, Core::Backend backend) : OrtModel(onnxModelPath, backend) {
}

std::vector<Face::Detection> Yolov7Face::detect(const cv::Mat &input) {
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
    std::vector<std::array<Face::Point, 5>> pts;

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

            std::array<Face::Point, 5> pt{
                {
                    {
                        cv::Point(
                            int((*(data + 6) - xyScale.x) * xyScale.scale),
                            int((*(data + 7) - xyScale.y) * xyScale.scale)
                        ),
                        *(data + 8),
                    },
                    {
                        cv::Point(
                            int((*(data + 9) - xyScale.x) * xyScale.scale),
                            int((*(data + 10) - xyScale.y) * xyScale.scale)
                        ),
                        *(data + 11),
                    },
                    {
                        cv::Point(
                            int((*(data + 12) - xyScale.x) * xyScale.scale),
                            int((*(data + 13) - xyScale.y) * xyScale.scale)
                        ),
                        *(data + 14),
                    },
                    {
                        cv::Point(
                            int((*(data + 15) - xyScale.x) * xyScale.scale),
                            int((*(data + 16) - xyScale.y) * xyScale.scale)
                        ),
                        *(data + 17),
                    },
                    {
                        cv::Point(
                            int((*(data + 18) - xyScale.x) * xyScale.scale),
                            int((*(data + 19) - xyScale.y) * xyScale.scale)
                        ),
                        *(data + 20),
                    },
                }
            };

            pts.emplace_back(pt);
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

void Yolov7Face::preprocess(const cv::Mat &input, cv::Mat &blob, XyScale &xyScale) {
    ImgProc::letterbox(input, blob, modelInputShape, xyScale);
    ImgProc::hwcToNchw(blob, blob);
    ImgProc::scale(blob);
}
