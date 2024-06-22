#ifndef ASSISTANT_UTILS_VISUALIZE_H
#define ASSISTANT_UTILS_VISUALIZE_H

#include "core/structures.h"

class Visualize {
public:
    static void drawFaceDetections(const cv::Mat &input, const std::vector<Face::Detection> &detections);

    static void blurFaces(const cv::Mat &input, const std::vector<Face::Detection> &detections);

private:
    Visualize() {
    }
};

#endif //ASSISTANT_UTILS_VISUALIZE_H
