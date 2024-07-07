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
}

#endif //ASSISTANT_CORE_ALGORITHMS_H
