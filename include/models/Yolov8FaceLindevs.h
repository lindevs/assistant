#ifndef ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H
#define ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H

#include "models/YoloFaceLindevs.h"

class Yolov8FaceLindevs : public YoloFaceLindevs {
public:
    explicit Yolov8FaceLindevs(const std::string &onnxModelPath, Core::Backend backend = Core::Backend::CPU);
};

#endif //ASSISTANT_MODELS_YOLOV8_FACE_LINDEVS_H
