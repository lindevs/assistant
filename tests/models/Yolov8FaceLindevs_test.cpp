#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/Yolov8FaceLindevs.h"

TEST(Yolov8FaceLindevsTests, DetectTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    Yolov8FaceLindevs model("testsdata/models/yolov8n-face-lindevs.onnx");
    std::vector<Face::Detection> detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    ASSERT_NEAR(detections[0].confidence, 0.886014103f, 0.000001f);
    ASSERT_NEAR(detections[1].confidence, 0.863056659f, 0.000001f);

    std::vector x = {detections[0].box.x, detections[1].box.x};
    EXPECT_THAT(x, testing::ElementsAre(235, 789));

    std::vector y = {detections[0].box.y, detections[1].box.y};
    EXPECT_THAT(y, testing::ElementsAre(24, 34));

    std::vector width = {detections[0].box.width, detections[1].box.width};
    EXPECT_THAT(width, testing::ElementsAre(149, 152));

    std::vector height = {detections[0].box.height, detections[1].box.height};
    EXPECT_THAT(height, testing::ElementsAre(202, 223));
}
