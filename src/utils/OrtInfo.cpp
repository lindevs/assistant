#include <onnxruntime_cxx_api.h>
#include "utils/OrtInfo.h"

std::vector<Core::Backend> OrtInfo::getBackends() {
    if (backends.empty()) {
        backends.emplace_back(Core::Backend::CPU);

        std::vector<std::string> providers = Ort::GetAvailableProviders();
        for (const auto &provider: providers) {
            if ("CUDAExecutionProvider" == provider) {
                backends.emplace_back(Core::Backend::CUDA);
                break;
            }
        }
    }

    return backends;
}
