#ifndef ASSISTANT_UTILS_RESIZE_H
#define ASSISTANT_UTILS_RESIZE_H

#include <opencv2/core/mat.hpp>

class ImgResize {
public:
    enum InterpolationMethods {
        INTERPOLATION_NEAREST = 0,
        INTERPOLATION_LANCZOS = 1,
        INTERPOLATION_BILINEAR = 2,
        INTERPOLATION_BICUBIC = 3,
        INTERPOLATION_BOX = 4,
        INTERPOLATION_HAMMING = 5,
    };

    static cv::Mat resize(const cv::Mat &src, const cv::Size &size, int32_t filter);

private:
    static constexpr uint32_t precisionBits = 32 - 8 - 2;

    class Filter {
    public:
        explicit Filter(double support) : support{support} {};

        [[nodiscard]] virtual double filter(double x) const = 0;

        [[nodiscard]] double getSupport() const { return support; };

    private:
        double support;
    };

    class BoxFilter : public Filter {
    public:
        BoxFilter() : Filter(0.5) {};

        [[nodiscard]] double filter(double x) const override;
    };

    class BilinearFilter : public Filter {
    public:
        BilinearFilter() : Filter(1.0) {};

        [[nodiscard]] double filter(double x) const override;
    };

    class HammingFilter : public Filter {
    public:
        HammingFilter() : Filter(1.0) {};

        [[nodiscard]] double filter(double x) const override;
    };

    class BicubicFilter : public Filter {
    public:
        BicubicFilter() : Filter(2.0) {};

        [[nodiscard]] double filter(double x) const override;
    };

    class LanczosFilter : public Filter {
    public:
        LanczosFilter() : Filter(3.0) {};

        [[nodiscard]] double filter(double x) const override;

    private:
        static double sincFilter(double x);
    };

    using preprocessCoefficientsFn = std::vector<double> (*)(const std::vector<double> &);

    template<typename T> using outMapFn = T (*)(double);

    static cv::Mat resample(const cv::Mat &imIn, int32_t xSize, int32_t ySize,
                            const std::shared_ptr<Filter> &filterP, const cv::Vec4f &rect);

    static void resampleHorizontal(cv::Mat &imOut, const cv::Mat &imIn, int32_t offset, int32_t ksize,
                                   const std::vector<int32_t> &bounds, const std::vector<double> &prekk);

    template<typename T>
    static void resampleHorizontal(cv::Mat &imOut, const cv::Mat &imIn, int32_t offset, int32_t ksize,
                                   const std::vector<int32_t> &bounds, const std::vector<double> &prekk,
                                   preprocessCoefficientsFn preprocessCoefficients = nullptr, double initBuffer = 0.0,
                                   outMapFn<T> outMap = nullptr);

    static void resampleVertical(cv::Mat &imOut, const cv::Mat &imIn, int32_t ksize,
                                 const std::vector<int32_t> &bounds, const std::vector<double> &prekk);

    static cv::Mat resampleNearest(const cv::Mat &imIn, int32_t xSize, int32_t ySize, const cv::Vec4f &rect);

    static int32_t precomputeCoeffs(int32_t inSize, double in0, double in1, int32_t outSize,
                                    const std::shared_ptr<Filter> &filterP, std::vector<int32_t> &bounds,
                                    std::vector<double> &kk);

    static std::vector<double> normalizeCoeffs8bpc(const std::vector<double> &prekk);

    static uint8_t clip8(double in);
};

#endif //ASSISTANT_UTILS_RESIZE_H
