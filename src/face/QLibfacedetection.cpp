#include "face/QFaceDetection.h"
#include "models/Libfacedetection.h"
#include "models/Yolov8FaceLindevs.h"

void QFaceDetection::start(const Face::Params &params) {
    switch (params.model.id) {
        case Face::MODEL_YOLOV8N_FACE_LINDEVS:
        case Face::MODEL_YOLOV8S_FACE_LINDEVS:
        case Face::MODEL_YOLOV8M_FACE_LINDEVS:
        case Face::MODEL_YOLOV8L_FACE_LINDEVS:
        case Face::MODEL_YOLOV8X_FACE_LINDEVS:
            model = new Yolov8FaceLindevs(std::string(params.path) + "/" + params.model.file);
            break;
        case Face::MODEL_LIBFACEDETECTION:
        default:
            model = new Libfacedetection();
    }
}

void QFaceDetection::stop() {
    delete model;
    model = nullptr;
}

void QFaceDetection::detect(const cv::Mat &img) {
    emit detected(model->detect(img), img);
}
