#include "face/QLibfacedetection.h"

void QLibfacedetection::detect(const cv::Mat &img) {
    emit detected(libfacedetection.detect(img), img);
}
