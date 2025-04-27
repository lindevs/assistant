#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/Libfacedetection.h"

TEST(LibfacedetectionTests, DetectTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/detection/face.jpg");

    Libfacedetection model;
    const std::vector detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    EXPECT_EQ(detections[0].confidence, 0.94f);
    EXPECT_EQ(detections[1].confidence, 0.94f);

    EXPECT_EQ(detections[0].box.x, 233);
    EXPECT_EQ(detections[1].box.x, 790);

    EXPECT_EQ(detections[0].box.y, 21);
    EXPECT_EQ(detections[1].box.y, 49);

    EXPECT_EQ(detections[0].box.width, 150);
    EXPECT_EQ(detections[1].box.width, 147);

    EXPECT_EQ(detections[0].box.height, 202);
    EXPECT_EQ(detections[1].box.height, 205);
}
