#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/Yolov5Face.h"

TEST(Yolov5FaceTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    Yolov5Face model(TESTS_DATA "/models/yolov5n-0.5-face.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_NEAR(detections[0].confidence, 0.868725359f, 0.000001f);
    EXPECT_NEAR(detections[1].confidence, 0.868083357f, 0.000001f);

    EXPECT_EQ(detections[0].box.x, 230);
    EXPECT_EQ(detections[1].box.x, 782);

    EXPECT_EQ(detections[0].box.y, 14);
    EXPECT_EQ(detections[1].box.y, 33);

    EXPECT_EQ(detections[0].box.width, 159);
    EXPECT_EQ(detections[1].box.width, 162);

    EXPECT_EQ(detections[0].box.height, 217);
    EXPECT_EQ(detections[1].box.height, 225);

    EXPECT_EQ(detections[0].rightEye.pt.x, 290);
    EXPECT_EQ(detections[1].rightEye.pt.x, 843);

    EXPECT_EQ(detections[0].rightEye.pt.y, 96);
    EXPECT_EQ(detections[1].rightEye.pt.y, 124);

    EXPECT_EQ(detections[0].leftEye.pt.x, 355);
    EXPECT_EQ(detections[1].leftEye.pt.x, 909);

    EXPECT_EQ(detections[0].leftEye.pt.y, 98);
    EXPECT_EQ(detections[1].leftEye.pt.y, 137);

    EXPECT_EQ(detections[0].nose.pt.x, 330);
    EXPECT_EQ(detections[1].nose.pt.x, 879);

    EXPECT_EQ(detections[0].nose.pt.y, 132);
    EXPECT_EQ(detections[1].nose.pt.y, 164);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.x, 289);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.x, 838);

    EXPECT_EQ(detections[0].mouthRightCorner.pt.y, 166);
    EXPECT_EQ(detections[1].mouthRightCorner.pt.y, 196);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.x, 347);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.x, 892);

    EXPECT_EQ(detections[0].mouthLeftCorner.pt.y, 169);
    EXPECT_EQ(detections[1].mouthLeftCorner.pt.y, 207);
}
