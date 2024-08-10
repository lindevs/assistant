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
    const int MODEL_ULTRA_FACE_SLIM_320 = 6;
    const int MODEL_ULTRA_FACE_RFB_320 = 7;
    const int MODEL_ULTRA_FACE_SLIM_640 = 8;
    const int MODEL_ULTRA_FACE_RFB_640 = 9;

    inline constexpr const char *MODEL_FILES[] = {
        nullptr,
        "yolov8n-face-lindevs.onnx",
        "yolov8s-face-lindevs.onnx",
        "yolov8m-face-lindevs.onnx",
        "yolov8l-face-lindevs.onnx",
        "yolov8x-face-lindevs.onnx",
        "ultraface-slim-320.onnx",
        "ultraface-rfb-320.onnx",
        "ultraface-slim-640.onnx",
        "ultraface-rfb-640.onnx",
    };

    inline constexpr const char *MODEL_YOLOV8_FACE_LINDEVS_URL = "https://github.com/lindevs/yolov8-face/releases";
    inline constexpr const char *MODEL_ULTRA_FACE_URL = "https://github.com/clibdev/Ultra-Light-Fast-Generic-Face-Detector-1MB/releases";

    inline constexpr const char *MODEL_URLS[] = {
        nullptr,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
    };
}

namespace Dedup {
    const int MODEL_MOBILE_NET_V3_SMALL_DEDUP = 0;

    inline constexpr const char *MODEL_FILES[] = {
        "mobilenetv3-small-dedup.onnx",
    };

    inline constexpr const char *MODEL_URLS[] = {
        "https://github.com/clibdev/imagededup/releases",
    };
}

#endif //ASSISTANT_CORE_MODELS_H
