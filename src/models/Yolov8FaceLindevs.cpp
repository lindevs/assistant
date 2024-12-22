#include "models/Yolov8FaceLindevs.h"
#include "utils/ImgProc.h"

Yolov8FaceLindevs::Yolov8FaceLindevs(const std::string &onnxModelPath, Core::Backend backend)
    : YoloFaceLindevs(onnxModelPath, backend) {
}
