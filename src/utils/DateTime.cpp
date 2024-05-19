#include <ctime>
#include <iomanip>
#include "utils/DateTime.h"

std::string DateTime::current() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d%H%M%S");

    return oss.str();
}
