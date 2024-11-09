#include "face/QFaceDetection.h"
#include "models/Libfacedetection.h"
#include "models/Yolov5Face.h"
#include "models/Yolov7Face.h"
#include "models/Yolov8FaceLindevs.h"
#include "models/Yolov9FaceLindevs.h"
#include "models/UltraFace.h"
#include "models/YoloFaceV2.h"
#include "models/RetinaFace.h"

void QFaceDetection::start(const Face::Params &params) {
    switch (params.detectionModel.id) {
        case Face::MODEL_LIBFACEDETECTION:
            model = new Libfacedetection();
            break;
        case Face::MODEL_YOLOV5_BLAZE_FACE:
        case Face::MODEL_YOLOV5N_05_FACE:
        case Face::MODEL_YOLOV5N_FACE:
        case Face::MODEL_YOLOV5S_FACE:
        case Face::MODEL_YOLOV5M_FACE:
        case Face::MODEL_YOLOV5L_FACE:
            model = new Yolov5Face(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_YOLOV7_LITE_T_FACE:
        case Face::MODEL_YOLOV7_LITE_S_FACE:
        case Face::MODEL_YOLOV7_TINY_FACE:
        case Face::MODEL_YOLOV7S_FACE:
        case Face::MODEL_YOLOV7_FACE:
        case Face::MODEL_YOLOV7_W6_FACE:
            model = new Yolov7Face(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_YOLOV8N_FACE_LINDEVS:
        case Face::MODEL_YOLOV8S_FACE_LINDEVS:
        case Face::MODEL_YOLOV8M_FACE_LINDEVS:
        case Face::MODEL_YOLOV8L_FACE_LINDEVS:
        case Face::MODEL_YOLOV8X_FACE_LINDEVS:
            model = new Yolov8FaceLindevs(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_YOLOV9T_FACE_LINDEVS:
        case Face::MODEL_YOLOV9S_FACE_LINDEVS:
        case Face::MODEL_YOLOV9M_FACE_LINDEVS:
        case Face::MODEL_YOLOV9C_FACE_LINDEVS:
        case Face::MODEL_YOLOV9E_FACE_LINDEVS:
            model = new Yolov9FaceLindevs(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_ULTRA_FACE_SLIM_320:
        case Face::MODEL_ULTRA_FACE_RFB_320:
        case Face::MODEL_ULTRA_FACE_SLIM_640:
        case Face::MODEL_ULTRA_FACE_RFB_640:
            model = new UltraFace(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_YOLO_FACE_V2:
            model = new YoloFaceV2(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        case Face::MODEL_RETINA_FACE_RESNET_50:
        case Face::MODEL_RETINA_FACE_MOBILENET_025:
            model = new RetinaFace(std::string(params.path) + "/" + params.detectionModel.file);
            break;
        default:
            model = nullptr;
    }
}

void QFaceDetection::stop() {
    delete model;
    model = nullptr;
}

void QFaceDetection::detect(const cv::Mat &img) {
    emit detected(model->detect(img));
}
