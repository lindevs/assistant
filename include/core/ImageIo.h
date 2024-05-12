#ifndef ASSISTANT_CORE_IMAGE_IO_H
#define ASSISTANT_CORE_IMAGE_IO_H

class ImageIo {
public:
    static cv::Mat read(const std::string &fullpath);

    static void write(const std::string &fullpath, cv::InputArray img);

    static void write(const std::string &path, const std::string &filename, cv::InputArray img);
};

#endif //ASSISTANT_CORE_IMAGE_IO_H
