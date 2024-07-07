#include "hash/QHashCalculation.h"
#include "utils/ImgProc.h"
#include "hash/AverageHash.h"
#include "hash/DifferenceHash.h"
#include "hash/PerceptualHash.h"

void QHashCalculation::start(const Hash::Params &params) {
    switch (params.algorithm.id) {
        case Hash::ALGORITHM_DIFFERENCE_HASH:
            algorithm = new DifferenceHash();
            break;
        case Hash::ALGORITHM_PERCEPTUAL_HASH:
            algorithm = new PerceptualHash();
            break;
        case Hash::ALGORITHM_AVERAGE_HASH:
        default:
            algorithm = new AverageHash();
    }
}

void QHashCalculation::stop() {
    delete algorithm;
    algorithm = nullptr;
}

void QHashCalculation::calculate(const cv::Mat &img) {
    emit calculated(ImgProc::hex(algorithm->calculate(img)).c_str());
}
