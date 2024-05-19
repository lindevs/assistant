#include <opencv2/imgproc.hpp>
#include "utils/Visualize.h"

void Visualize::drawFaceDetections(const cv::Mat &input, const std::vector<Face::Detection> &detections)
{
    cv::Scalar color(0, 255, 0);
    int thickness = 1;
    cv::Scalar textColor(0, 0, 0);
    int textThickness = 1;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    float fontScale = (float) thickness / 3.0f;
    char buff[5];

    size_t total = detections.size();
    for (int i = 0; i < total; ++i) {
        Face::Detection detection = detections[i];

        cv::rectangle(input, detection.box, color, thickness, cv::LINE_AA);

        std::sprintf(buff, "%.2f", detection.confidence);
        cv::Size textSize = cv::getTextSize(buff, font, fontScale, textThickness, nullptr);
        cv::Rect textBox(detection.box.x, detection.box.y - textSize.height - 3, textSize.width, textSize.height + 3);
        cv::Point textPos(detection.box.x, detection.box.y - 2);

        cv::rectangle(input, textBox, color, cv::FILLED, cv::LINE_AA);
        cv::putText(input, buff, textPos, font, fontScale, textColor, textThickness, cv::LINE_AA);
    }
}
