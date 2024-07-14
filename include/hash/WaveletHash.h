#ifndef ASSISTANT_HASH_WAVELET_HASH_H
#define ASSISTANT_HASH_WAVELET_HASH_H

#include <opencv2/core/mat.hpp>
#include "hash/HashAlgorithm.h"

class WaveletHash : public HashAlgorithm {
public:
    cv::Mat calculate(const cv::Mat &input) override;
};

#endif //ASSISTANT_HASH_WAVELET_HASH_H
