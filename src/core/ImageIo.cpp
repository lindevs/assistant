#include <opencv2/imgcodecs.hpp>
#include <filesystem>
#include "core/ImageIo.h"

cv::Mat ImageIo::read(const std::string &fullpath) {
    return cv::imread(fullpath);
}

void ImageIo::write(const std::string &fullpath, cv::InputArray img) {
    cv::imwrite(fullpath, img);
}

void ImageIo::write(const std::string &path, const std::string &filename, cv::InputArray img) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directories(path);
    }
    imwrite(path + "/" + filename, img);
}
