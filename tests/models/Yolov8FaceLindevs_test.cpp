#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/Yolov8FaceLindevs.h"

TEST(Yolov8FaceLindevsTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    Yolov8FaceLindevs model(TESTS_DATA "/models/yolov8n-face-lindevs.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_NEAR(detections[0].confidence, 0.886014103f, 0.000001f);
    EXPECT_NEAR(detections[1].confidence, 0.863056659f, 0.000001f);

    EXPECT_EQ(detections[0].box.x, 235);
    EXPECT_EQ(detections[1].box.x, 789);

    EXPECT_EQ(detections[0].box.y, 24);
    EXPECT_EQ(detections[1].box.y, 34);

    EXPECT_EQ(detections[0].box.width, 149);
    EXPECT_EQ(detections[1].box.width, 152);

    EXPECT_EQ(detections[0].box.height, 202);
    EXPECT_EQ(detections[1].box.height, 223);
}
