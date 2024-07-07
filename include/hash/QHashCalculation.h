#ifndef ASSISTANT_HASH_QHASH_CALCULATION_H
#define ASSISTANT_HASH_QHASH_CALCULATION_H

#include <QObject>
#include <opencv2/core/mat.hpp>
#include "hash/HashAlgorithm.h"

class QHashCalculation : public QObject {
Q_OBJECT

public:
    void start(const Hash::Params &params);

    void stop();

    void calculate(const cv::Mat &img);

signals:

    void calculated(const QString &hash);

private:
    HashAlgorithm *algorithm;
};

#endif //ASSISTANT_HASH_QHASH_CALCULATION_H
