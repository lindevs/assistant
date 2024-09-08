#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/MobileNetV3Dedup.h"

TEST(MobileNetV3DedupTests, EncodeTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    MobileNetV3Dedup model("testsdata/models/mobilenetv3-small-dedup.onnx");
    cv::Mat encoding = model.encode(img);

    ASSERT_EQ(encoding.total(), 576);
}
