#ifndef ASSISTANT_CORE_MODELS_H
#define ASSISTANT_CORE_MODELS_H

struct Model {
    int id = 0;
    const char *file = nullptr;
    const char *url = nullptr;

    bool operator!=(const Model &other) const {
        return id != other.id;
    }
};

namespace Face {
    const int MODEL_LIBFACEDETECTION = 0;
    const int MODEL_YOLOV8N_FACE_LINDEVS = 1;
    const int MODEL_YOLOV8S_FACE_LINDEVS = 2;
    const int MODEL_YOLOV8M_FACE_LINDEVS = 3;
    const int MODEL_YOLOV8L_FACE_LINDEVS = 4;
    const int MODEL_YOLOV8X_FACE_LINDEVS = 5;

    inline constexpr const char *MODEL_FILES[] = {
        nullptr,
        "yolov8n-face-lindevs.onnx",
        "yolov8s-face-lindevs.onnx",
        "yolov8m-face-lindevs.onnx",
        "yolov8l-face-lindevs.onnx",
        "yolov8x-face-lindevs.onnx",
    };

    inline constexpr const char *MODEL_YOLOV8_FACE_LINDEVS_URL = "https://github.com/lindevs/yolov8-face/releases";

    inline constexpr const char *MODEL_URLS[] = {
        nullptr,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
    };
}

#endif //ASSISTANT_CORE_MODELS_H
