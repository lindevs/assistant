#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include "utils/ImgIo.h"

cv::Mat ImgIo::read(const std::string &fullpath) {
    return cv::imread(fullpath);
}

cv::Mat ImgIo::readGrayscale(const std::string &fullpath) {
    return cv::imread(fullpath, cv::IMREAD_GRAYSCALE);
}

void ImgIo::write(const std::string &fullpath, cv::InputArray img) {
    cv::imwrite(fullpath, img);
}

void ImgIo::write(const std::string &path, const std::string &filename, cv::InputArray img) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    }
    imwrite(path + "/" + filename, img);
}
