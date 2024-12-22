#include "models/OrtModel.h"

OrtModel::OrtModel(const std::string &onnxModelPath, Core::Backend backend) {
#ifdef _WIN32
    auto path = std::wstring(onnxModelPath.begin(), onnxModelPath.end()).c_str();
#else
    auto path = onnxModelPath.c_str();
#endif

    sessionOptions.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
    if (backend == Core::Backend::CUDA) {
        OrtCUDAProviderOptions options{};
        options.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchHeuristic;
        sessionOptions.AppendExecutionProvider_CUDA(options);
    }
    session = Ort::Session(env, path, sessionOptions);

    Ort::AllocatorWithDefaultOptions allocator;

    inputNamesAlloc.emplace_back(session.GetInputNameAllocated(0, allocator));
    inputName = inputNamesAlloc[0].get();

    inputDims = session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
    inputDims[0] = 1;

    size_t outputCount = session.GetOutputCount();
    for (size_t i = 0; i < outputCount; ++i) {
        outputNamesAlloc.emplace_back(session.GetOutputNameAllocated(i, allocator));
        outputNames.emplace_back(outputNamesAlloc[i].get());

        outputDims.emplace_back(session.GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape());
        outputDims[i][0] = 1;
    }

    inputTensorSize = inputDims[1] * inputDims[2] * inputDims[3];
    modelInputShape = cv::Size((int) inputDims[3], (int) inputDims[2]);
}
