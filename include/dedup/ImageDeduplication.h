#ifndef ASSISTANT_DEDUP_IMAGE_DEDUPLICATION_H
#define ASSISTANT_DEDUP_IMAGE_DEDUPLICATION_H

#include "models/DeduplicationModel.h"

class ImageDeduplication {
public:
    explicit ImageDeduplication(DeduplicationModel *model);

    Dedup::Findings findDuplicates(const std::string &path);

private:
    DeduplicationModel *model;

    float modelScoreThreshold{0.95f};
};

#endif //ASSISTANT_DEDUP_IMAGE_DEDUPLICATION_H
