#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/ModNet.h"

TEST(ModNetTests, GenerateTest) {
    cv::Mat img = ImgIo::read("testsdata/images/generic/dog.jpg");

    ModNet model("testsdata/models/modnet-photographic.onnx");
    cv::Mat matte = model.generate(img);
    matte.convertTo(matte, CV_8U);
    matte = matte * 255;

    cv::Mat expected = ImgIo::readGrayscale("testsdata/images/result/modnet.bmp");

    bool const equal = std::equal(matte.begin<uchar>(), matte.end<uchar>(), expected.begin<uchar>());
    ASSERT_EQ(equal, true);
}
