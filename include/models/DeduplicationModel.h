#ifndef ASSISTANT_MODELS_DEDUPLICATION_MODEL_H
#define ASSISTANT_MODELS_DEDUPLICATION_MODEL_H

#include "core/structures.h"

class DeduplicationModel {
public:
    virtual ~DeduplicationModel() = default;

    virtual cv::Mat encode(const cv::Mat &input) = 0;
};

#endif //ASSISTANT_MODELS_DEDUPLICATION_MODEL_H
