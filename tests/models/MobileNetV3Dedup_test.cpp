#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/MobileNetV3Dedup.h"

TEST(MobileNetV3DedupTests, EncodeTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    MobileNetV3Dedup model(TESTS_DATA "/models/mobilenetv3-small-dedup.onnx");
    const cv::Mat encoding = model.encode(img);

   EXPECT_EQ(encoding.total(), 576);
}
