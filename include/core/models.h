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
    const int MODEL_YOLOV5_BLAZE_FACE = 1;
    const int MODEL_YOLOV5N_05_FACE = 2;
    const int MODEL_YOLOV5N_FACE = 3;
    const int MODEL_YOLOV5S_FACE = 4;
    const int MODEL_YOLOV5M_FACE = 5;
    const int MODEL_YOLOV5L_FACE = 6;
    const int MODEL_YOLOV8N_FACE_LINDEVS = 7;
    const int MODEL_YOLOV8S_FACE_LINDEVS = 8;
    const int MODEL_YOLOV8M_FACE_LINDEVS = 9;
    const int MODEL_YOLOV8L_FACE_LINDEVS = 10;
    const int MODEL_YOLOV8X_FACE_LINDEVS = 11;
    const int MODEL_ULTRA_FACE_SLIM_320 = 12;
    const int MODEL_ULTRA_FACE_RFB_320 = 13;
    const int MODEL_ULTRA_FACE_SLIM_640 = 14;
    const int MODEL_ULTRA_FACE_RFB_640 = 15;
    const int MODEL_YOLO_FACE_V2 = 16;

    inline constexpr const char *MODEL_FILES[] = {
        nullptr,
        "yolov5-blazeface.onnx",
        "yolov5n-0.5-face.onnx",
        "yolov5n-face.onnx",
        "yolov5s-face.onnx",
        "yolov5m-face.onnx",
        "yolov5l-face.onnx",
        "yolov8n-face-lindevs.onnx",
        "yolov8s-face-lindevs.onnx",
        "yolov8m-face-lindevs.onnx",
        "yolov8l-face-lindevs.onnx",
        "yolov8x-face-lindevs.onnx",
        "ultraface-slim-320.onnx",
        "ultraface-rfb-320.onnx",
        "ultraface-slim-640.onnx",
        "ultraface-rfb-640.onnx",
        "yolo-facev2.onnx",
    };

    inline constexpr const char *MODEL_YOLOV5_FACE_URL = "https://github.com/clibdev/yolov5-face/releases";
    inline constexpr const char *MODEL_YOLOV8_FACE_LINDEVS_URL = "https://github.com/lindevs/yolov8-face/releases";
    inline constexpr const char *MODEL_ULTRA_FACE_URL = "https://github.com/clibdev/Ultra-Light-Fast-Generic-Face-Detector-1MB/releases";
    inline constexpr const char *MODEL_YOLO_FACE_V2_URL = "https://github.com/clibdev/YOLO-FaceV2/releases";

    inline constexpr const char *MODEL_URLS[] = {
        nullptr,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_YOLO_FACE_V2_URL,
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
