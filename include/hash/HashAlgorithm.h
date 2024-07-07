#ifndef ASSISTANT_MODELS_HASH_HASH_ALGORITHM_H
#define ASSISTANT_MODELS_HASH_HASH_ALGORITHM_H

#include "core/structures.h"

class HashAlgorithm {
public:
    virtual ~HashAlgorithm() = default;

    virtual cv::Mat calculate(const cv::Mat &input) = 0;
};

#endif //ASSISTANT_MODELS_HASH_HASH_ALGORITHM_H
