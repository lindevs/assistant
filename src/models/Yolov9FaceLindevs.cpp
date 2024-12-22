#include "models/Yolov9FaceLindevs.h"
#include "utils/ImgProc.h"

Yolov9FaceLindevs::Yolov9FaceLindevs(const std::string &onnxModelPath, Core::Backend backend)
    : YoloFaceLindevs(onnxModelPath, backend) {
}
