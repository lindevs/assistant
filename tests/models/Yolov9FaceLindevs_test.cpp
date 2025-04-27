#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/Yolov9FaceLindevs.h"

TEST(Yolov9FaceLindevsTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    Yolov9FaceLindevs model(TESTS_DATA "/models/yolov9t-face-lindevs.onnx");
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_NEAR(detections[0].confidence, 0.869481742f, 0.000001f);
    EXPECT_NEAR(detections[1].confidence, 0.849224567f, 0.000001f);

    EXPECT_EQ(detections[0].box.x, 235);
    EXPECT_EQ(detections[1].box.x, 790);

    EXPECT_EQ(detections[0].box.y, 22);
    EXPECT_EQ(detections[1].box.y, 34);

    EXPECT_EQ(detections[0].box.width, 148);
    EXPECT_EQ(detections[1].box.width, 147);

    EXPECT_EQ(detections[0].box.height, 203);
    EXPECT_EQ(detections[1].box.height, 219);
}
