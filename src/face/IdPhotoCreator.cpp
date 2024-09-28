#include <opencv2/imgproc.hpp>
#include "face/IdPhotoCreator.h"

cv::Mat IdPhotoCreator::create(const cv::Mat &img, const cv::Mat &alpha, const cv::Rect &face) {
    cv::Mat enhancedAlpha;
    enhanceAlphaChannel(alpha, enhancedAlpha);

    cv::Mat imgAlpha;
    appendAlphaChannel(img, enhancedAlpha, imgAlpha);

    cv::Mat photo;
    cropIdPhoto(imgAlpha, face, photo);

    return photo;
}

void IdPhotoCreator::enhanceAlphaChannel(const cv::Mat &alpha, cv::Mat &enhancedAlpha) {
    cv::copyMakeBorder(alpha, enhancedAlpha, 10, 10, 10, 10, cv::BORDER_CONSTANT, cv::Scalar(0));

    cv::Mat tmp;
    cv::threshold(enhancedAlpha, tmp, 127, 255, cv::THRESH_BINARY);
    cv::erode(tmp, tmp, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)), cv::Point(-1, -1), 3);

    std::vector<std::vector<cv::Point> > contours;
    cv::Mat hierarchy;
    cv::findContours(tmp, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    std::sort(contours.begin(), contours.end(), [](const std::vector<cv::Point> &p1, const std::vector<cv::Point> &p2) {
        return cv::contourArea(p1) > cv::contourArea(p2);
    });
    cv::Mat contour = cv::Mat::zeros(enhancedAlpha.size(), CV_8UC1);
    cv::drawContours(contour, contours, 0, cv::Scalar(255), 2);

    cv::Mat mask = cv::Mat::zeros(enhancedAlpha.rows + 2, enhancedAlpha.cols + 2, CV_8UC1);
    cv::floodFill(contour, mask, cv::Point(0, 0), cv::Scalar(255));

    cv::add(enhancedAlpha, 255 - contour, enhancedAlpha);
    enhancedAlpha = enhancedAlpha(cv::Rect(10, 10, enhancedAlpha.cols - 20, enhancedAlpha.rows - 20));
}

void IdPhotoCreator::appendAlphaChannel(const cv::Mat &img, const cv::Mat &alpha, cv::Mat &output) {
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    channels.push_back(alpha);
    cv::merge(channels, output);
}

void IdPhotoCreator::cropIdPhoto(const cv::Mat &img, const cv::Rect &face, cv::Mat &photo) {
    float heightWidthRatio = (float) photoSize.height / (float) photoSize.width;

    cv::Size2f faceCenter((float) face.x + (float) face.width / 2.0f, (float) face.y + (float) face.height / 2.0f);
    int faceMeasure = face.width * face.height;
    float cropMeasure = (float) faceMeasure / headMeasureRatio;
    float resizeRatio = cropMeasure / (float) (photoSize.width * photoSize.height);
    double resizeRatioSingle = std::sqrt(resizeRatio);
    cv::Size cropSize((int) (photoSize.width * resizeRatioSingle), (int) (photoSize.height * resizeRatioSingle));

    int x1 = (int) (faceCenter.width - (float) cropSize.width / 2.0f);
    int y1 = (int) (faceCenter.height - (float) cropSize.height * headHeightRatio);
    int x2 = x1 + cropSize.width;
    int y2 = y1 + cropSize.height;

    cropImageWithPadding(x1, y1, x2, y2, img, photo);
    cv::resize(photo, photo, cropSize);

    std::vector<int> cords = getBoundingBoxMargins(photo);
    int yTop = cords[0];
    int xLeft = cords[2];
    int xRight = cords[3];

    int statusLeftRight = 0;
    int cutValueTop = 0;
    if (xLeft > 0 || xRight > 0) {
        statusLeftRight = 1;
        cutValueTop = (int) ((float) (xLeft + xRight) * heightWidthRatio / 2.0);
    }

    std::vector<int> moves = calculateTopOffset(yTop - cutValueTop, cropSize.height);
    int statusTop = moves[0];
    int moveValue = moves[1];

    if (statusLeftRight != 0 || statusTop != 0) {
        cropImageWithPadding(
            x1 + xLeft,
            y1 + cutValueTop + statusTop * moveValue,
            x2 - xRight,
            y2 - cutValueTop + statusTop * moveValue,
            img,
            photo
        );
    }

    moveImageToBottom(photo, photo);
    resizeIdPhoto(photo, photo);
}

void IdPhotoCreator::cropImageWithPadding(int x1, int y1, int x2, int y2, const cv::Mat &img, cv::Mat &output) {
    cv::Size cropSize(y2 - y1, x2 - x1);

    int x1a = 0;
    int y1a = 0;
    if (y1 < 0) {
        y1a = std::abs(y1);
        y1 = 0;
    }
    if (y2 > img.rows) {
        y2 = img.rows;
    }
    if (x1 < 0) {
        x1a = std::abs(x1);
        x1 = 0;
    }
    if (x2 > img.cols) {
        x2 = img.cols;
    }

    cv::Mat background(cropSize.width, cropSize.height, img.type(), cv::Scalar(255, 255, 255, 0));
    cv::Rect roi(x1, y1, x2 - x1, y2 - y1);
    cv::Mat croppedImg = img(roi);
    croppedImg.copyTo(background(cv::Rect(x1a, y1a, croppedImg.cols, croppedImg.rows)));

    output = background;
}

std::vector<int> IdPhotoCreator::getBoundingBoxMargins(const cv::Mat &img) {
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat alpha = channels[3];
    cv::threshold(alpha, alpha, 127, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point> > contours;
    cv::Mat hierarchy;
    cv::findContours(alpha, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat temp(img.size(), img.type(), cv::Scalar(255, 255, 255, 255));
    cv::drawContours(temp, contours, -1, cv::Scalar(0, 0, 255), -1);

    std::vector<double> contoursArea;
    for (const auto &cnt: contours) {
        contoursArea.push_back(cv::contourArea(cnt));
    }
    auto maxAreaIter = std::max_element(contoursArea.begin(), contoursArea.end());
    size_t idx = std::distance(contoursArea.begin(), maxAreaIter);

    cv::Rect bbox = cv::boundingRect(contours[idx]);
    int x = bbox.x;
    int y = bbox.y;
    int w = bbox.width;
    int h = bbox.height;

    int height = img.rows;
    int width = img.cols;
    int yUp = y >= 0 ? y : 0;
    int yDown = y + h < height ? y + h : height - 1;
    int xLeft = x >= 0 ? x : 0;
    int xRight = x + w < width ? x + w : width - 1;

    return {yUp, height - yDown, xLeft, width - xRight};
}

std::vector<int> IdPhotoCreator::calculateTopOffset(int val, int cropHeight) {
    float value = (float) val / (float) cropHeight;
    if (topDistanceMin <= value && value <= topDistanceMax) {
        return {0, 0};
    }

    if (value > topDistanceMax) {
        double moveValue = value - topDistanceMax;

        return {1, int(moveValue * cropHeight)};
    }

    double moveValue = topDistanceMin - value;

    return {-1, int(moveValue * cropHeight)};
}

void IdPhotoCreator::moveImageToBottom(const cv::Mat &img, cv::Mat &output) {
    std::vector<int> cords = getBoundingBoxMargins(img);
    int yBottom = cords[1];

    cv::Mat tmp(yBottom, img.cols, img.type(), cv::Scalar(0, 0, 0, 0));
    output = img(cv::Rect(0, 0, img.cols, img.rows - yBottom));
    cv::vconcat(tmp, output, output);
}

void IdPhotoCreator::resizeIdPhoto(const cv::Mat &img, cv::Mat &output) {
    float resizeRatio = (float) img.rows / (float) photoSize.height;
    int resizeItem = (int) (std::round(resizeRatio));

    if (resizeRatio >= 2) {
        for (int i = 0; i < resizeItem - 1; ++i) {
            cv::Size size(photoSize.width * (resizeItem - i - 1), photoSize.height * (resizeItem - i - 1));
            if (i == 0) {
                cv::resize(img, output, size, 0, 0, cv::INTER_AREA);
            } else {
                cv::resize(output, output, size, 0, 0, cv::INTER_AREA);
            }
        }
    } else {
        cv::resize(img, output, photoSize, 0, 0, cv::INTER_AREA);
    }
}
