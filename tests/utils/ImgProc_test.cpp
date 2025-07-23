#include <gtest/gtest.h>
#include <opencv2/core.hpp>
#include "utils/ImgProc.h"

cv::Mat createBgr();

cv::Mat createRgb();

cv::Mat createBgra();

TEST(ImgProcTests, hwcToNchwTest) {
    cv::Mat img = createBgr();
    ImgProc::hwcToNchw(img, img);

    const std::vector expected{
        26, 27, 28, 29, 30, 31, 32, 33, 18, 19, 20, 21,
        22, 23, 24, 25, 10, 11, 12, 13, 14, 15, 16, 17,
    };

    ASSERT_EQ(img.dims, 4);
    ASSERT_EQ(img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(img.data[i], expected[i]);
    }
}

TEST(ImgProcTests, nmsTest) {
    const std::vector boxes{
        cv::Rect2f(64, 264, 141, 81), cv::Rect2f(64, 264, 141, 81), cv::Rect2f(64, 264, 140, 81),
        cv::Rect2f(190, 98, 84, 277), cv::Rect2f(190, 98, 84, 276), cv::Rect2f(403, 138, 198, 207),
        cv::Rect2f(403, 138, 199, 208), cv::Rect2f(403, 138, 199, 208), cv::Rect2f(191, 98, 84, 276),
        cv::Rect2f(191, 99, 84, 276), cv::Rect2f(403, 139, 199, 207), cv::Rect2f(403, 139, 199, 206),
        cv::Rect2f(403, 138, 199, 207), cv::Rect2f(190, 99, 84, 276), cv::Rect2f(191, 99, 83, 276),
        cv::Rect2f(403, 139, 199, 207), cv::Rect2f(190, 97, 84, 278),
    };
    const std::vector confidences{
        0.823272109f, 0.833828211f, 0.810037434f, 0.85497117f, 0.845267296f, 0.834753692f,
        0.847511172f, 0.815787077f, 0.879196882f, 0.869076133f, 0.827022612f, 0.852620244f,
        0.821513414f, 0.86394918f, 0.831187785f, 0.837420642f, 0.812889636f,
    };
    std::vector<int> indices;

    ImgProc::nms(boxes, confidences, 0.5f, indices);

    const std::vector expected{8, 11, 1};

    ASSERT_EQ(indices.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(indices[i], expected[i]);
    }
}

TEST(ImgProcTests, resizeTest) {
    cv::Mat img = createBgr();
    ImgProc::resize(img, img, cv::Size(1, 3));

    const std::vector expected{11, 19, 27, 14, 22, 30, 15, 23, 31};

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(img.data[i], expected[i]);
    }
}

TEST(ImgProcTests, resizeAreaTest) {
    cv::Mat img = createBgr();
    ImgProc::resizeArea(img, img, cv::Size(1, 3));

    const std::vector expected{11, 19, 27, 13, 21, 29, 15, 23, 31};

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(img.data[i], expected[i]);
    }
}

TEST(ImgProcTests, computeSizeForResizeWithRefSizeTest) {
    // src.w > src.h and (src.w and src.h) < ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(500, 419), 512), cv::Size(608, 512));
    // src.w > src.h and (src.w and src.h) > ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(600, 519), 512), cv::Size(576, 512));
    // src.w < src.h and (src.w and src.h) < ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(419, 500), 512), cv::Size(512, 608));
    // src.w < src.h and (src.w and src.h) > ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(519, 600), 512), cv::Size(512, 576));
    // src.w = src.h and (src.w and src.h) < ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(500, 500), 512), cv::Size(512, 512));
    // src.w = src.h and (src.w and src.h) > ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(600, 600), 512), cv::Size(512, 512));
    // src.w = src.h = ref
    EXPECT_EQ(ImgProc::computeSizeForResize(cv::Size(512, 512), 512), cv::Size(512, 512));
}

TEST(ImgProcTests, letterboxTest) {
    XyScale xyScale;
    cv::Mat img = createBgr();
    ImgProc::letterbox(img, img, cv::Size(5, 5), xyScale);

    const std::vector expected{
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        10, 18, 26, 11, 19, 27, 12, 20, 28, 12, 20, 28, 13, 21, 29,
        14, 22, 30, 15, 23, 31, 16, 24, 32, 16, 24, 32, 17, 25, 33,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
    };

    EXPECT_EQ(xyScale.x, 0);
    EXPECT_EQ(xyScale.y, 1);
    EXPECT_EQ(xyScale.scale, 0.8f);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(img.data[i], expected[i]);
    }
}

TEST(ImgProcTests, scaleTest) {
    cv::Mat img = createBgr();
    ImgProc::scale(img);

    const std::vector expected{
        0.0392156877f, 0.0705882385f, 0.101960793f, 0.0431372561f, 0.0745098069f, 0.105882362f,
        0.0470588282f, 0.0784313753f, 0.10980393f, 0.0509803966f, 0.0823529437f, 0.113725498f,
        0.054901965f, 0.0862745121f, 0.117647067f, 0.0588235334f, 0.0901960805f, 0.121568635f,
        0.0627451f, 0.0941176564f, 0.125490203f, 0.0666666701f, 0.0980392247f, 0.129411772f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, scaleSizeTest) {
    EXPECT_EQ(ImgProc::scale(cv::Size(224, 128), 0.875f), cv::Size(256, 146));
}

TEST(ImgProcTests, convertToFloatTest) {
    cv::Mat img = createBgr();
    ImgProc::convertToFloat(img);

    ASSERT_EQ(img.type() & CV_MAT_DEPTH_MASK, CV_32F);

    const std::vector expected{
        10.0f, 18.0f, 26.0f, 11.0f, 19.0f, 27.0f, 12.0f, 20.0f, 28.0f, 13.0f, 21.0f, 29.0f,
        14.0f, 22.0f, 30.0f, 15.0f, 23.0f, 31.0f, 16.0f, 24.0f, 32.0f, 17.0f, 25.0f, 33.0f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, normalizeMeanTest) {
    cv::Mat img = createBgr();
    img.convertTo(img, CV_32F);
    ImgProc::normalize(img, cv::Scalar(1.5f, 2.5f, 3.5f));

    const std::vector expected{
        8.5f, 15.5f, 22.5f, 9.5f, 16.5f, 23.5f, 10.5f, 17.5f, 24.5f, 11.5f, 18.5f, 25.5f,
        12.5f, 19.5f, 26.5f, 13.5f, 20.5f, 27.5f, 14.5f, 21.5f, 28.5f, 15.5f, 22.5f, 29.5f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, normalizeStdTest) {
    cv::Mat img = createBgr();
    img.convertTo(img, CV_32F);
    ImgProc::normalize(img, cv::Scalar(1, 2, 3), cv::Scalar(2, 4, 8));

    const std::vector expected{
        4.5f, 4.0f, 2.875f, 5.0f, 4.25f, 3.0f, 5.5f, 4.5f, 3.125f, 6.0f, 4.75f, 3.25f,
        6.5f, 5.0f, 3.375f, 7.0f, 5.25f, 3.5f, 7.5f, 5.5f, 3.625f, 8.0f, 5.75f, 3.75f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, scaleAndNormalizeTest) {
    cv::Mat img = createBgr();
    constexpr float mean[3]{1, 2, 3};
    constexpr float std[3]{2, 4, 8};
    ImgProc::scaleAndNormalize(img, mean, std);

    const std::vector expected{
        -0.480392158f, -0.482352942f, -0.362254888f, -0.478431374f, -0.481372535f, -0.361764699f,
        -0.47647059f, -0.480392158f, -0.361274511f, -0.474509805f, -0.479411751f, -0.360784322f,
        -0.472549021f, -0.478431374f, -0.360294104f, -0.470588237f, -0.477450967f, -0.359803915f,
        -0.468627453f, -0.47647059f, -0.359313726f, -0.466666669f, -0.475490183f, -0.358823538f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, meanTest) {
    const cv::Mat img = createBgr();
    const cv::Scalar actual = ImgProc::mean(img);

    const std::vector expected{13.5f, 21.5f, 29.5f};

    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, centerCropTest) {
    cv::Mat img = createBgr();
    ImgProc::centerCrop(img, cv::Size(2, 1));

    const std::vector expected{11, 19, 27, 12, 20, 28};

    ASSERT_EQ(3 * img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(img.data[i], expected[i]);
    }
}

TEST(ImgProcTests, jaccardIndexTest) {
    EXPECT_EQ(ImgProc::jaccardIndex(cv::Rect2f(190, 98, 84, 277), cv::Rect2f(190, 98, 84, 276)), 0.996389866f);
    EXPECT_EQ(ImgProc::jaccardIndex(cv::Rect2f(0, 0, 0, 0), cv::Rect2f(0, 0, 0, 0)), 0.0f);
}

TEST(ImgProcTests, bgr2grayTest) {
    const cv::Mat img = createBgr();
    cv::Mat gray;
    ImgProc::bgr2gray(img, gray);

    const std::vector expected{19, 20, 21, 22, 23, 24, 25, 26};

    ASSERT_EQ(gray.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(gray.data[i], expected[i]);
    }
}

TEST(ImgProcTests, rgb2bgrTest) {
    const cv::Mat img = createRgb();
    cv::Mat bgr;
    ImgProc::rgb2bgr(img, bgr);

    const std::vector expected{
        10, 18, 26, 11, 19, 27, 12, 20, 28, 13, 21, 29,
        14, 22, 30, 15, 23, 31, 16, 24, 32, 17, 25, 33,
    };

    ASSERT_EQ(3 * bgr.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(bgr.data[i], expected[i]);
    }
}

TEST(ImgProcTests, bgra2rgbaTest) {
    const cv::Mat img = createBgra();
    cv::Mat rgba;
    ImgProc::bgra2rgba(img, rgba);

    const std::vector expected{
        26, 18, 10, 1, 27, 19, 11, 2, 28, 20, 12, 3, 29, 21, 13, 4,
        30, 22, 14, 5, 31, 23, 15, 6, 32, 24, 16, 7, 33, 25, 17, 8,
    };

    ASSERT_EQ(4 * rgba.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(rgba.data[i], expected[i]);
    }
}

TEST(ImgProcTests, dctTest) {
    float data[][4]{
        {100, 101, 102, 103},
        {10,  11,  103, 104},
    };
    cv::Mat img(2, 4, CV_32F, &data);
    ImgProc::dct(img, img);

    const std::vector expected{
        224.15285f, -62.602936f, 0.0f, 24.400251f,
        62.9325104f, 59.448616f, 0.0f, -24.624422f,
    };
    const auto *actual = reinterpret_cast<float *>(img.data);

    ASSERT_EQ(img.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, dwt2Test) {
    float data[][4]{
        {100, 101, 102, 103},
        {10,  11,  103, 104},
    };
    const cv::Mat img(2, 4, CV_32F, &data);
    cv::Mat temp;
    ImgProc::dwt2(img, temp, 1);

    const std::vector expected{111, 206, 0, 0, 90, -1, -1, -1};
    const auto *actual = reinterpret_cast<float *>(temp.data);

    ASSERT_EQ(temp.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(actual[i], expected[i]);
    }
}

TEST(ImgProcTests, hashTest) {
    uchar data[][8]{
        {0, 255, 255, 255, 255, 255, 255, 255},
        {0, 255, 0,   255, 255, 255, 255, 255},
        {0, 0,   0,   0,   0,   0,   0,   255},
        {0, 0,   0,   0,   0,   0,   0,   255},
        {0, 0,   0,   0,   255, 255, 255, 255},
        {0, 0,   0,   255, 255, 255, 255, 255},
        {0, 0,   0,   0,   0,   0,   255, 255},
        {0, 0,   0,   0,   0,   0,   0,   255},
    };
    const cv::Mat img(8, 8, CV_8U, &data);
    cv::Mat temp(1, 8, CV_8U);
    ImgProc::hash(img, temp);

    const std::vector expected{127, 95, 1, 1, 15, 31, 3, 1};

    ASSERT_EQ(temp.total(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(temp.data[i], expected[i]);
    }
}

TEST(ImgProcTests, hexTest) {
    uchar data[][8]{{127, 95, 1, 1, 15, 31, 3, 1}};
    const cv::Mat hash(1, 8, CV_8U, &data);

    EXPECT_EQ(ImgProc::hex(hash), "7f5f01010f1f0301");
}

TEST(ImgProcTests, cosineSimilarityTest) {
    float data1[][8]{
        {0.87682962f, 0.070774801f, -0.092280522f, -0.15983361f, -0.11459824f, 0.79937744f, 0.076851681f, 0.083315045f},
    };
    const cv::Mat x(1, 8, CV_32F, &data1);
    float data2[][8]{
        {0.8239274f, 0.13613346f, 0.088873714f, 0.054075729f, 0.0238578f, 0.25603119f, 0.36077952f, 0.055261601f},
    };
    const cv::Mat y(1, 8, CV_32F, &data2);

    EXPECT_NEAR(ImgProc::cosineSimilarity(x, y), 0.82124705752820049, 0.000001f);
}

cv::Mat createBgr() {
    uchar blue[][4]{
        {10, 11, 12, 13},
        {14, 15, 16, 17},
    };
    uchar green[][4]{
        {18, 19, 20, 21},
        {22, 23, 24, 25},
    };
    uchar red[][4]{
        {26, 27, 28, 29},
        {30, 31, 32, 33},
    };
    const cv::Mat blueChannel(2, 4, CV_8U, &blue);
    const cv::Mat greenChannel(2, 4, CV_8U, &green);
    const cv::Mat redChannel(2, 4, CV_8U, &red);

    cv::Mat bgr;
    const std::vector channels{blueChannel, greenChannel, redChannel};
    cv::merge(channels, bgr);

    return bgr;
}

cv::Mat createRgb() {
    uchar red[][4]{
        {26, 27, 28, 29},
        {30, 31, 32, 33},
    };
    uchar green[][4]{
        {18, 19, 20, 21},
        {22, 23, 24, 25},
    };
    uchar blue[][4]{
        {10, 11, 12, 13},
        {14, 15, 16, 17},
    };
    const cv::Mat redChannel(2, 4, CV_8U, &red);
    const cv::Mat greenChannel(2, 4, CV_8U, &green);
    const cv::Mat blueChannel(2, 4, CV_8U, &blue);

    cv::Mat rgb;
    const std::vector channels{redChannel, greenChannel, blueChannel};
    cv::merge(channels, rgb);

    return rgb;
}

cv::Mat createBgra() {
    uchar blue[][4]{
        {10, 11, 12, 13},
        {14, 15, 16, 17},
    };
    uchar green[][4]{
        {18, 19, 20, 21},
        {22, 23, 24, 25},
    };
    uchar red[][4]{
        {26, 27, 28, 29},
        {30, 31, 32, 33},
    };
    uchar alpha[][4]{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
    };
    const cv::Mat blueChannel(2, 4, CV_8U, &blue);
    const cv::Mat greenChannel(2, 4, CV_8U, &green);
    const cv::Mat redChannel(2, 4, CV_8U, &red);
    const cv::Mat alphaChannel(2, 4, CV_8U, &alpha);

    cv::Mat bgra;
    const std::vector channels{blueChannel, greenChannel, redChannel, alphaChannel};
    cv::merge(channels, bgra);

    return bgra;
}
