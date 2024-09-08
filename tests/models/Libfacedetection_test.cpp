#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/ImgIo.h"
#include "models/Libfacedetection.h"

TEST(LibfacedetectionTests, DetectTest) {
    cv::Mat img = ImgIo::read("testsdata/images/detection/face.jpg");

    Libfacedetection model;
    std::vector<Face::Detection> detections = model.detect(img);

    ASSERT_EQ(detections.size(), 2);

    std::vector confidence = {detections[0].confidence, detections[1].confidence};
    EXPECT_THAT(confidence, testing::ElementsAre(0.94f, 0.94f));

    std::vector x = {detections[0].box.x, detections[1].box.x};
    EXPECT_THAT(x, testing::ElementsAre(233, 790));

    std::vector y = {detections[0].box.y, detections[1].box.y};
    EXPECT_THAT(y, testing::ElementsAre(21, 49));

    std::vector width = {detections[0].box.width, detections[1].box.width};
    EXPECT_THAT(width, testing::ElementsAre(150, 147));

    std::vector height = {detections[0].box.height, detections[1].box.height};
    EXPECT_THAT(height, testing::ElementsAre(202, 205));
}
