#ifndef ASSISTANT_CORE_APP_H
#define ASSISTANT_CORE_APP_H

namespace Core {
    inline constexpr const char *ORG = "Lindevs";
    inline constexpr const char *APP = "Assistant";

    enum Backend {
        CPU = 0,
        CUDA = 1,
    };
}

#endif //ASSISTANT_CORE_APP_H
