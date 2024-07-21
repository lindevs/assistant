#include "utils/Formatting.h"

std::string Formatting::formatDuplications(const Dedup::Findings &findings, const size_t index) {
    char buff[5];

    std::string text = findings.images[index];
    for (const auto &duplication: findings.duplications[index]) {
        std::sprintf(buff, "%.2f", duplication.confidence);
        text += '\n' + findings.images[duplication.index] + " (" + buff + ')';
    }

    return text;
}
