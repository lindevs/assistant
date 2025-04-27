#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/UltraFace.h"

TEST(UltraFaceTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    UltraFace model(TESTS_DATA "/models/ultraface-rfb-640.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_EQ(detections[0].confidence, 0.999965191f);
    EXPECT_EQ(detections[1].confidence, 0.99948895f);

    EXPECT_EQ(detections[0].box.x, 240);
    EXPECT_EQ(detections[1].box.x, 794);

    EXPECT_EQ(detections[0].box.y, 25);
    EXPECT_EQ(detections[1].box.y, 46);

    EXPECT_EQ(detections[0].box.width, 142);
    EXPECT_EQ(detections[1].box.width, 142);

    EXPECT_EQ(detections[0].box.height, 197);
    EXPECT_EQ(detections[1].box.height, 204);
}
