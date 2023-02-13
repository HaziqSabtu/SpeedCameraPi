#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <chrono>
#include <opencv2/opencv.hpp>

struct ImageData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;

    ImageData() {}

    ImageData(cv::Mat image,
              std::chrono::high_resolution_clock::time_point time)
        : image(image), time(time) {}

    ImageData(cv::Mat image)
        : image(image), time(std::chrono::high_resolution_clock::now()) {}

    double TimeDiff(ImageData &data) {
        return std::chrono::duration_cast<std::chrono::microseconds>(time -
                                                                     data.time)
            .count();
    }
};

#endif