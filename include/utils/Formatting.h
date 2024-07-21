#ifndef ASSISTANT_UTILS_FORMATTING_H
#define ASSISTANT_UTILS_FORMATTING_H

#include "core/structures.h"

class Formatting {
public:
    static std::string formatDuplications(const Dedup::Findings &findings, size_t index);

private:
    Formatting() {
    }
};

#endif //ASSISTANT_UTILS_FORMATTING_H
