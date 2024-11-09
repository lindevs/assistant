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
    const int MODEL_YOLOV7_LITE_T_FACE = 7;
    const int MODEL_YOLOV7_LITE_S_FACE = 8;
    const int MODEL_YOLOV7_TINY_FACE = 9;
    const int MODEL_YOLOV7S_FACE = 10;
    const int MODEL_YOLOV7_FACE = 11;
    const int MODEL_YOLOV7_W6_FACE = 12;
    const int MODEL_YOLOV8N_FACE_LINDEVS = 13;
    const int MODEL_YOLOV8S_FACE_LINDEVS = 14;
    const int MODEL_YOLOV8M_FACE_LINDEVS = 15;
    const int MODEL_YOLOV8L_FACE_LINDEVS = 16;
    const int MODEL_YOLOV8X_FACE_LINDEVS = 17;
    const int MODEL_YOLOV9T_FACE_LINDEVS = 18;
    const int MODEL_YOLOV9S_FACE_LINDEVS = 19;
    const int MODEL_YOLOV9M_FACE_LINDEVS = 20;
    const int MODEL_YOLOV9C_FACE_LINDEVS = 21;
    const int MODEL_YOLOV9E_FACE_LINDEVS = 22;
    const int MODEL_ULTRA_FACE_SLIM_320 = 23;
    const int MODEL_ULTRA_FACE_RFB_320 = 24;
    const int MODEL_ULTRA_FACE_SLIM_640 = 25;
    const int MODEL_ULTRA_FACE_RFB_640 = 26;
    const int MODEL_YOLO_FACE_V2 = 27;
    const int MODEL_RETINA_FACE_RESNET_50 = 28;
    const int MODEL_RETINA_FACE_MOBILENET_025 = 29;

    inline constexpr const char *MODEL_FILES[] = {
        nullptr,
        "yolov5-blazeface.onnx",
        "yolov5n-0.5-face.onnx",
        "yolov5n-face.onnx",
        "yolov5s-face.onnx",
        "yolov5m-face.onnx",
        "yolov5l-face.onnx",
        "yolov7-lite-t-face.onnx",
        "yolov7-lite-s-face.onnx",
        "yolov7-tiny-face.onnx",
        "yolov7s-face.onnx",
        "yolov7-face.onnx",
        "yolov7-w6-face.onnx",
        "yolov8n-face-lindevs.onnx",
        "yolov8s-face-lindevs.onnx",
        "yolov8m-face-lindevs.onnx",
        "yolov8l-face-lindevs.onnx",
        "yolov8x-face-lindevs.onnx",
        "yolov9t-face-lindevs.onnx",
        "yolov9s-face-lindevs.onnx",
        "yolov9m-face-lindevs.onnx",
        "yolov9c-face-lindevs.onnx",
        "yolov9e-face-lindevs.onnx",
        "ultraface-slim-320.onnx",
        "ultraface-rfb-320.onnx",
        "ultraface-slim-640.onnx",
        "ultraface-rfb-640.onnx",
        "yolo-facev2.onnx",
        "retinaface-resnet-50.onnx",
        "retinaface-mobilenet-0.25.onnx",
    };

    inline constexpr const char *MODEL_YOLOV5_FACE_URL = "https://github.com/clibdev/yolov5-face/releases";
    inline constexpr const char *MODEL_YOLOV7_FACE_URL = "https://github.com/clibdev/yolov7-face/releases";
    inline constexpr const char *MODEL_YOLOV8_FACE_LINDEVS_URL = "https://github.com/lindevs/yolov8-face/releases";
    inline constexpr const char *MODEL_YOLOV9_FACE_LINDEVS_URL = "https://github.com/lindevs/yolov9-face/releases";
    inline constexpr const char *MODEL_ULTRA_FACE_URL = "https://github.com/clibdev/Ultra-Light-Fast-Generic-Face-Detector-1MB/releases";
    inline constexpr const char *MODEL_YOLO_FACE_V2_URL = "https://github.com/clibdev/YOLO-FaceV2/releases";
    inline constexpr const char *MODEL_RETINA_FACE_URL = "https://github.com/clibdev/Pytorch_Retinaface/releases";

    inline constexpr const char *MODEL_URLS[] = {
        nullptr,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV5_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV7_FACE_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV8_FACE_LINDEVS_URL,
        MODEL_YOLOV9_FACE_LINDEVS_URL,
        MODEL_YOLOV9_FACE_LINDEVS_URL,
        MODEL_YOLOV9_FACE_LINDEVS_URL,
        MODEL_YOLOV9_FACE_LINDEVS_URL,
        MODEL_YOLOV9_FACE_LINDEVS_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_ULTRA_FACE_URL,
        MODEL_YOLO_FACE_V2_URL,
        MODEL_RETINA_FACE_URL,
        MODEL_RETINA_FACE_URL,
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

namespace Matting {
    const int MODEL_MODNET_PHOTOGRAPHIC = 0;

    inline constexpr const char *MODEL_FILES[] = {
        "modnet-photographic.onnx",
    };

    inline constexpr const char *MODEL_URLS[] = {
        "https://github.com/clibdev/MODNet/releases",
    };
}

#endif //ASSISTANT_CORE_MODELS_H
