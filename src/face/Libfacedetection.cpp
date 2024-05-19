#include <facedetection/facedetectcnn.h>
#include "face/Libfacedetection.h"

std::vector<Face::Detection> Libfacedetection::detect(const cv::Mat &img) const {
    unsigned char buffer[0x9000];
    int *results = facedetect_cnn(buffer, img.data, img.cols, img.rows, (int) img.step);
    auto *data = (short *) (results + 1);

    std::vector<Face::Detection> detections{};
    detections.reserve(*results);
    for (int i = 0; i < *results; ++i) {
        if (*data >= modelScoreThreshold) {
            detections.emplace_back(
                (float) *data / 100,
                cv::Rect(*(data + 1), *(data + 2), *(data + 3), *(data + 4))
            );
        }
        data += 16;
    }

    return detections;
}
