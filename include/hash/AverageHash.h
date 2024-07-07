#ifndef ASSISTANT_HASH_AVERAGE_HASH_H
#define ASSISTANT_HASH_AVERAGE_HASH_H

#include <opencv2/core/mat.hpp>
#include "hash/HashAlgorithm.h"

class AverageHash : public HashAlgorithm {
public:
    cv::Mat calculate(const cv::Mat &input) override;
};

#endif //ASSISTANT_HASH_AVERAGE_HASH_H
