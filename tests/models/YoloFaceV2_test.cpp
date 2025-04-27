#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/YoloFaceV2.h"

TEST(YoloFaceV2FaceTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    YoloFaceV2 model(TESTS_DATA "/models/yolo-facev2.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_NEAR(detections[0].confidence, 0.877800405f, 0.000001f);
    EXPECT_NEAR(detections[1].confidence, 0.877227485f, 0.000001f);

    EXPECT_EQ(detections[0].box.x, 789);
    EXPECT_EQ(detections[1].box.x, 237);

    EXPECT_EQ(detections[0].box.y, 34);
    EXPECT_EQ(detections[1].box.y, 22);

    EXPECT_EQ(detections[0].box.width, 152);
    EXPECT_EQ(detections[1].box.width, 145);

    EXPECT_EQ(detections[0].box.height, 220);
    EXPECT_EQ(detections[1].box.height, 203);
}
