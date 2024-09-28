#ifndef ASSISTANT_FACE_ID_PHOTO_CREATOR_H
#define ASSISTANT_FACE_ID_PHOTO_CREATOR_H

#include <opencv2/core/mat.hpp>

class IdPhotoCreator {
public:
    cv::Mat create(const cv::Mat &img, const cv::Mat &alpha, const cv::Rect &face);

private:
    const float headMeasureRatio{0.2f};
    const float headHeightRatio{0.45f};
    const float topDistanceMax{0.12f};
    const float topDistanceMin{0.1f};
    const cv::Size photoSize{295, 413};

    static void enhanceAlphaChannel(const cv::Mat &alpha, cv::Mat &enhancedAlpha);

    static void appendAlphaChannel(const cv::Mat &img, const cv::Mat &alpha, cv::Mat &output);

    void cropIdPhoto(const cv::Mat &img, const cv::Rect &face, cv::Mat &photo);

    static void cropImageWithPadding(int x1, int y1, int x2, int y2, const cv::Mat &img, cv::Mat &output);

    static std::vector<int> getBoundingBoxMargins(const cv::Mat &img);

    std::vector<int> calculateTopOffset(int val, int cropHeight);

    static void moveImageToBottom(const cv::Mat &img, cv::Mat &output);

    void resizeIdPhoto(const cv::Mat &img, cv::Mat &output);
};

#endif //ASSISTANT_FACE_ID_PHOTO_CREATOR_H
