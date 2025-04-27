#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/RetinaFace.h"

TEST(RetinaFaceTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    RetinaFace model(TESTS_DATA "/models/retinaface-mobilenet-0.25.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_EQ(detections[0].confidence, 0.998887f);
    EXPECT_EQ(detections[1].confidence, 0.998074412f);

    EXPECT_EQ(detections[0].box.x, 790);
    EXPECT_EQ(detections[1].box.x, 243);

    EXPECT_EQ(detections[0].box.y, 52);
    EXPECT_EQ(detections[1].box.y, 34);

    EXPECT_EQ(detections[0].box.width, 149);
    EXPECT_EQ(detections[1].box.width, 143);

    EXPECT_EQ(detections[0].box.height, 203);
    EXPECT_EQ(detections[1].box.height, 188);

    EXPECT_EQ(detections[0].rightEye.pt.x, 844);
    EXPECT_EQ(detections[1].rightEye.pt.x, 288);

    EXPECT_EQ(detections[0].rightEye.pt.y, 124);
    EXPECT_EQ(detections[1].rightEye.pt.y, 98);

    EXPECT_EQ(detections[0].leftEye.pt.x, 913);
    EXPECT_EQ(detections[1].leftEye.pt.x, 356);

    EXPECT_EQ(detections[0].leftEye.pt.y, 137);
    EXPECT_EQ(detections[1].leftEye.pt.y, 104);

    EXPECT_EQ(detections[0].nose.pt.x, 880);
    EXPECT_EQ(detections[1].nose.pt.x, 324);

    EXPECT_EQ(detections[0].nose.pt.y, 166);
    EXPECT_EQ(detections[1].nose.pt.y, 125);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.x, 834);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.x, 283);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.y, 196);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.y, 165);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.x, 893);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.x, 343);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.y, 207);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.y, 170);
}
