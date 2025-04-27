#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/Yolov7Face.h"

TEST(Yolov7FaceTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    Yolov7Face model(TESTS_DATA "/models/yolov7-lite-t-face.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_NEAR(detections[0].confidence, 0.885704040f, 0.000001f);
    EXPECT_NEAR(detections[1].confidence, 0.874399960f, 0.000001f);

    EXPECT_EQ(detections[0].box.x, 238);
    EXPECT_EQ(detections[1].box.x, 792);

    EXPECT_EQ(detections[0].box.y, 24);
    EXPECT_EQ(detections[1].box.y, 44);

    EXPECT_EQ(detections[0].box.width, 147);
    EXPECT_EQ(detections[1].box.width, 144);

    EXPECT_EQ(detections[0].box.height, 200);
    EXPECT_EQ(detections[1].box.height, 208);

    EXPECT_NEAR(detections[0].rightEye.confidence, 0.997240781f, 0.000001f);
    EXPECT_NEAR(detections[1].rightEye.confidence, 0.997264325f, 0.000001f);

    EXPECT_EQ(detections[0].rightEye.pt.x, 294);
    EXPECT_EQ(detections[1].rightEye.pt.x, 843);

    EXPECT_EQ(detections[0].rightEye.pt.y, 93);
    EXPECT_EQ(detections[1].rightEye.pt.y, 124);

    EXPECT_NEAR(detections[0].leftEye.confidence, 0.996528744f, 0.000001f);
    EXPECT_NEAR(detections[1].leftEye.confidence, 0.996622204f, 0.000001f);

    EXPECT_EQ(detections[0].leftEye.pt.x, 358);
    EXPECT_EQ(detections[1].leftEye.pt.x, 908);

    EXPECT_EQ(detections[0].leftEye.pt.y, 104);
    EXPECT_EQ(detections[1].leftEye.pt.y, 131);

    EXPECT_NEAR(detections[0].nose.confidence, 0.997262239f, 0.000001f);
    EXPECT_NEAR(detections[1].nose.confidence, 0.997292757f, 0.000001f);

    EXPECT_EQ(detections[0].nose.pt.x, 333);
    EXPECT_EQ(detections[1].nose.pt.x, 880);

    EXPECT_EQ(detections[0].nose.pt.y, 128);
    EXPECT_EQ(detections[1].nose.pt.y, 168);

    EXPECT_NEAR(detections[0].mouthRightCorner.confidence, 0.995762825f, 0.000001f);
    EXPECT_NEAR(detections[1].mouthRightCorner.confidence, 0.995210528f, 0.000001f);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.x, 290);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.x, 841);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.y, 163);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.y, 197);

    EXPECT_NEAR(detections[0].mouthLeftCorner.confidence, 0.990095019f, 0.000001f);
    EXPECT_NEAR(detections[1].mouthLeftCorner.confidence, 0.989299654f, 0.000001f);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.x, 349);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.x, 897);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.y, 173);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.y, 203);
}
