#ifndef ASSISTANT_CORE_ALGORITHMS_H
#define ASSISTANT_CORE_ALGORITHMS_H

struct Algorithm {
    int id = 0;

    bool operator!=(const Algorithm &other) const {
        return id != other.id;
    }
};

namespace Hash {
    const int ALGORITHM_AVERAGE_HASH = 0;
    const int ALGORITHM_DIFFERENCE_HASH = 1;
    const int ALGORITHM_PERCEPTUAL_HASH = 2;
    const int ALGORITHM_WAVELET_HASH = 3;
}

#endif //ASSISTANT_CORE_ALGORITHMS_H
