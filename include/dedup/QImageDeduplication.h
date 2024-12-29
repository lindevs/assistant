#ifndef ASSISTANT_DEDUP_QIMAGE_DEDUPLICATION_H
#define ASSISTANT_DEDUP_QIMAGE_DEDUPLICATION_H

#include <QObject>
#include <opencv2/core/mat.hpp>
#include "dedup/ImageDeduplication.h"

class QImageDeduplication : public QObject {
Q_OBJECT

public:
    void start(const Dedup::Params &params);

    void stop();

    void findDuplicates(const QString &path);

signals:

    void found(const Dedup::Findings &findings);

private:
    DeduplicationModel *model = nullptr;
    ImageDeduplication *deduplication = nullptr;
};

#endif //ASSISTANT_DEDUP_QIMAGE_DEDUPLICATION_H
