#ifndef ASSISTANT_UTILS_IMAGE_IO_H
#define ASSISTANT_UTILS_IMAGE_IO_H

#include <opencv2/core/mat.hpp>

class ImgIo {
public:
    static cv::Mat read(const std::string &fullpath);

    static void write(const std::string &fullpath, cv::InputArray img);

    static void write(const std::string &path, const std::string &filename, cv::InputArray img);
};

#endif //ASSISTANT_UTILS_IMAGE_IO_H
