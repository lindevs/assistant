#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/Yolov7Face.h"

TEST(Yolov7FaceTests, DetectTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    Yolov7Face model("testsdata/models/yolov7-lite-t-face.onnx");
    std::vector<Face::Detection> detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    ASSERT_NEAR(detections[0].confidence, 0.885704040f, 0.000001f);
    ASSERT_NEAR(detections[1].confidence, 0.874399960f, 0.000001f);

    std::vector x = {detections[0].box.x, detections[1].box.x};
    EXPECT_THAT(x, testing::ElementsAre(238, 792));

    std::vector y = {detections[0].box.y, detections[1].box.y};
    EXPECT_THAT(y, testing::ElementsAre(24, 44));

    std::vector width = {detections[0].box.width, detections[1].box.width};
    EXPECT_THAT(width, testing::ElementsAre(147, 144));

    std::vector height = {detections[0].box.height, detections[1].box.height};
    EXPECT_THAT(height, testing::ElementsAre(200, 208));

    x = {detections[0].rightEye.pt.x, detections[1].rightEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(294, 843));

    y = {detections[0].rightEye.pt.y, detections[1].rightEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(93, 124));

    ASSERT_NEAR(detections[0].rightEye.confidence, 0.997240781f, 0.000001f);
    ASSERT_NEAR(detections[1].rightEye.confidence, 0.997264325f, 0.000001f);

    x = {detections[0].leftEye.pt.x, detections[1].leftEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(358, 908));

    y = {detections[0].leftEye.pt.y, detections[1].leftEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(104, 131));

    ASSERT_NEAR(detections[0].leftEye.confidence, 0.996528744f, 0.000001f);
    ASSERT_NEAR(detections[1].leftEye.confidence, 0.996622204f, 0.000001f);

    x = {detections[0].nose.pt.x, detections[1].nose.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(333, 880));

    y = {detections[0].nose.pt.y, detections[1].nose.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(128, 168));

    ASSERT_NEAR(detections[0].nose.confidence, 0.997262239f, 0.000001f);
    ASSERT_NEAR(detections[1].nose.confidence, 0.997292757f, 0.000001f);

    x = {detections[0].mouthRightCorner.pt.x, detections[1].mouthRightCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(290, 841));

    y = {detections[0].mouthRightCorner.pt.y, detections[1].mouthRightCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(163, 197));

    ASSERT_NEAR(detections[0].mouthRightCorner.confidence, 0.995762825f, 0.000001f);
    ASSERT_NEAR(detections[1].mouthRightCorner.confidence, 0.995210528f, 0.000001f);

    x = {detections[0].mouthLeftCorner.pt.x, detections[1].mouthLeftCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(349, 897));

    y = {detections[0].mouthLeftCorner.pt.y, detections[1].mouthLeftCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(173, 203));

    ASSERT_NEAR(detections[0].mouthLeftCorner.confidence, 0.990095019f, 0.000001f);
    ASSERT_NEAR(detections[1].mouthLeftCorner.confidence, 0.989299654f, 0.000001f);
}
