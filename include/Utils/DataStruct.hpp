/**
 * @file DataStruct.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Data Structures
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <Utils/Struct/D_Hough.hpp>
#include <Utils/Struct/D_OpticalFlow.hpp>
#include <chrono>
#include <opencv2/opencv.hpp>

struct ImageData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
    Detection::HoughData hough;
    Detection::OpticalFlowData flow;

    ImageData() {}

    ImageData(cv::Mat image,
              std::chrono::high_resolution_clock::time_point time)
        : image(image), time(time), hough(), flow() {}

    ImageData(cv::Mat image)
        : image(image), time(std::chrono::high_resolution_clock::now()),
          hough(), flow() {}

    void SetHough(Detection::HoughData hough) { this->hough = hough; }
    void SetFlow(Detection::OpticalFlowData flow) { this->flow = flow; }
    double TimeDiff(ImageData &data) {
        return std::chrono::duration_cast<std::chrono::microseconds>(time -
                                                                     data.time)
            .count();
    }
};

struct SpeedData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
    std::vector<cv::Point2f> points;

    cv::Point2f BottomLine() {
        // same Implementation as in ObjectDetection
        std::vector<cv::Point2f> tmp;
        tmp.assign(points.begin(), points.end());
        std::sort(tmp.begin(), tmp.end(),
                  [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
        return tmp.front();
    }
};

#endif