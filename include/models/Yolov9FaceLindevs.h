#ifndef ASSISTANT_MODELS_YOLOV9_FACE_LINDEVS_H
#define ASSISTANT_MODELS_YOLOV9_FACE_LINDEVS_H

#include "models/YoloFaceLindevs.h"

class Yolov9FaceLindevs : public YoloFaceLindevs {
public:
    explicit Yolov9FaceLindevs(const std::string &onnxModelPath);
};

#endif //ASSISTANT_MODELS_YOLOV9_FACE_LINDEVS_H
