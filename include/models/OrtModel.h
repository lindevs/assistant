#ifndef ASSISTANT_MODELS_ORT_MODEL_H
#define ASSISTANT_MODELS_ORT_MODEL_H

#include <onnxruntime_cxx_api.h>
#include "core/structures.h"

class OrtModel {
public:
    explicit OrtModel(const std::string &onnxModelPath);

protected:
    const Ort::Env env = Ort::Env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "OrtModel");
    const Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    const Ort::RunOptions runOptions;
    Ort::SessionOptions sessionOptions;
    Ort::Session session;

    std::vector<Ort::AllocatedStringPtr> inputNamesAlloc;
    std::vector<Ort::AllocatedStringPtr> outputNamesAlloc;
    const char *inputName;
    std::vector<const char *> outputNames;

    std::vector<int64_t> inputDims;
    std::vector<std::vector<int64_t>> outputDims;

    size_t inputTensorSize;
    cv::Size modelInputShape;
};

#endif //ASSISTANT_MODELS_ORT_MODEL_H
