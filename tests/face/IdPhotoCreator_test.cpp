#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "face/IdPhotoCreator.h"

TEST(IdPhotoCreatorTests, CreateTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/id_photo/face.jpg");
    const cv::Mat alpha = ImgIo::readGrayscale(TESTS_DATA "/images/id_photo/alpha.bmp");

    IdPhotoCreator creator;
    const cv::Mat photo = creator.create(img, alpha, cv::Rect(211, 122, 147, 201));

    const cv::Mat expected = ImgIo::read(TESTS_DATA "/images/id_photo/result.png");

    const bool equal = std::equal(photo.begin<uchar>(), photo.end<uchar>(), expected.begin<uchar>());
    EXPECT_EQ(equal, true);
}
