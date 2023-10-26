#pragma once

#include <chrono>
#include <opencv2/core/mat.hpp>

using namespace std::chrono;

#define HPTime std::chrono::high_resolution_clock::time_point
#define CDVector std::vector<CaptureData>

/**
 * @brief Data for Capturing Images
 *
 */
struct CaptureData {
    cv::Mat image;
    HPTime time;

    CaptureData();
    CaptureData(cv::Mat image);
    CaptureData(cv::Mat image, HPTime time);

    bool operator==(const CaptureData &other) const;
    CaptureData clone() const;
    CaptureData &operator=(const CaptureData &other);
};
