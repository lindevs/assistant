#ifndef ASSISTANT_FACE_LIBFACEDETECTION_H
#define ASSISTANT_FACE_LIBFACEDETECTION_H

#include <opencv2/core/mat.hpp>
#include "core/structures.h"

class Libfacedetection {
public:
    [[nodiscard]] std::vector<Face::Detection> detect(const cv::Mat &img) const;

private:
    const int modelScoreThreshold = 80;
};

#endif //ASSISTANT_FACE_LIBFACEDETECTION_H
