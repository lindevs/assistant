#include <gtest/gtest.h>
#include "utils/ImgIo.h"
#include "models/ModNet.h"

TEST(ModNetTests, GenerateTest) {
    const cv::Mat img = ImgIo::read(TESTS_DATA "/images/generic/dog.jpg");

    ModNet model(TESTS_DATA "/models/modnet-photographic.onnx");
    cv::Mat matte = model.generate(img);
    matte.convertTo(matte, CV_8U);
    matte = matte * 255;

    const cv::Mat expected = ImgIo::readGrayscale(TESTS_DATA "/images/result/modnet.bmp");

    const bool equal = std::equal(matte.begin<uchar>(), matte.end<uchar>(), expected.begin<uchar>());
    EXPECT_EQ(equal, true);
}
