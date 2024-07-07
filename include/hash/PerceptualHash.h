#ifndef ASSISTANT_HASH_PERCEPTUAL_HASH_H
#define ASSISTANT_HASH_PERCEPTUAL_HASH_H

#include <opencv2/core/mat.hpp>
#include "hash/HashAlgorithm.h"

class PerceptualHash : public HashAlgorithm {
public:
    cv::Mat calculate(const cv::Mat &input) override;
};

#endif //ASSISTANT_HASH_PERCEPTUAL_HASH_H
