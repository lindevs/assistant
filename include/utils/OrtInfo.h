#ifndef ASSISTANT_UTILS_ORT_INFO_H
#define ASSISTANT_UTILS_ORT_INFO_H

#include <vector>
#include "core/app.h"

class OrtInfo {
public:
    static std::vector<Core::Backend> getBackends();

private:
    OrtInfo() {
    }

    static inline std::vector<Core::Backend> backends;
};

#endif //ASSISTANT_UTILS_ORT_INFO_H
