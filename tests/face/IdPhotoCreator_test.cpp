#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "face/IdPhotoCreator.h"

TEST(IdPhotoCreatorTests, CreateTest) {
    cv::Mat img = ImgIo::read("testsdata/images/id_photo/face.jpg");
    cv::Mat alpha = ImgIo::readGrayscale("testsdata/images/id_photo/alpha.bmp");

    IdPhotoCreator creator;
    cv::Mat photo = creator.create(img, alpha, cv::Rect(211, 122, 147, 201));

    cv::Mat expected = ImgIo::read("testsdata/images/id_photo/result.png");

    bool const equal = std::equal(photo.begin<uchar>(), photo.end<uchar>(), expected.begin<uchar>());
    ASSERT_EQ(equal, true);
}
