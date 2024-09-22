#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/RetinaFace.h"

TEST(RetinaFaceTests, DetectTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    RetinaFace model("testsdata/models/retinaface-mobilenet-0.25.onnx");
    std::vector<Face::Detection> detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    std::vector confidence = {detections[0].confidence, detections[1].confidence};
    EXPECT_THAT(confidence, testing::ElementsAre(0.998887f, 0.998074412f));

    std::vector x = {detections[0].box.x, detections[1].box.x};
    EXPECT_THAT(x, testing::ElementsAre(790, 243));

    std::vector y = {detections[0].box.y, detections[1].box.y};
    EXPECT_THAT(y, testing::ElementsAre(52, 34));

    std::vector width = {detections[0].box.width, detections[1].box.width};
    EXPECT_THAT(width, testing::ElementsAre(149, 143));

    std::vector height = {detections[0].box.height, detections[1].box.height};
    EXPECT_THAT(height, testing::ElementsAre(203, 188));

    x = {detections[0].rightEye.pt.x, detections[1].rightEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(844, 288));

    y = {detections[0].rightEye.pt.y, detections[1].rightEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(124, 98));

    x = {detections[0].leftEye.pt.x, detections[1].leftEye.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(913, 356));

    y = {detections[0].leftEye.pt.y, detections[1].leftEye.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(137, 104));

    x = {detections[0].nose.pt.x, detections[1].nose.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(880, 324));

    y = {detections[0].nose.pt.y, detections[1].nose.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(166, 125));

    x = {detections[0].mouthRightCorner.pt.x, detections[1].mouthRightCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(834, 283));

    y = {detections[0].mouthRightCorner.pt.y, detections[1].mouthRightCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(196, 165));

    x = {detections[0].mouthLeftCorner.pt.x, detections[1].mouthLeftCorner.pt.x};
    EXPECT_THAT(x, testing::ElementsAre(893, 343));

    y = {detections[0].mouthLeftCorner.pt.y, detections[1].mouthLeftCorner.pt.y};
    EXPECT_THAT(y, testing::ElementsAre(207, 170));
}
