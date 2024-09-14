#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/Yolov5Face.h"

TEST(Yolov5FaceTests, DetectTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    Yolov5Face model("testsdata/models/yolov5n-0.5-face.onnx");
    std::vector<Face::Detection> detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    ASSERT_NEAR(detections[0].confidence, 0.868725359f, 0.000001f);
    ASSERT_NEAR(detections[1].confidence, 0.868083357f, 0.000001f);

    std::vector x = {detections[0].box.x, detections[1].box.x};
    EXPECT_THAT(x, testing::ElementsAre(230, 782));

    std::vector y = {detections[0].box.y, detections[1].box.y};
    EXPECT_THAT(y, testing::ElementsAre(14, 33));

    std::vector width = {detections[0].box.width, detections[1].box.width};
    EXPECT_THAT(width, testing::ElementsAre(159, 162));

    std::vector height = {detections[0].box.height, detections[1].box.height};
    EXPECT_THAT(height, testing::ElementsAre(217, 225));

    x = {detections[0].rightEye.pt.x, detections[1].rightEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(290, 843));

    y = {detections[0].rightEye.pt.y, detections[1].rightEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(96, 124));

    x = {detections[0].leftEye.pt.x, detections[1].leftEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(355, 909));

    y = {detections[0].leftEye.pt.y, detections[1].leftEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(98, 137));

    x = {detections[0].nose.pt.x, detections[1].nose.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(330, 879));

    y = {detections[0].nose.pt.y, detections[1].nose.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(132, 164));

    x = {detections[0].mouthRightCorner.pt.x, detections[1].mouthRightCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(289, 838));

    y = {detections[0].mouthRightCorner.pt.y, detections[1].mouthRightCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(166, 196));

    x = {detections[0].mouthLeftCorner.pt.x, detections[1].mouthLeftCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(347, 892));

    y = {detections[0].mouthLeftCorner.pt.y, detections[1].mouthLeftCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(169, 207));
}
