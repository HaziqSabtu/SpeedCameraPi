#pragma once

#include <opencv2/core.hpp>

#define ADVector std::vector<AllignData>

/**
 * @brief Data for Alligning Images
 *
 */
struct AllignData {

    // The alligned Image
    cv::Mat image;

    // The transformation Matrix
    cv::Mat transformMatrix;

    AllignData();
    AllignData(cv::Mat image, cv::Mat transformMatrix);

    bool operator==(const AllignData &other) const;
    AllignData clone() const;
    AllignData &operator=(const AllignData &other);
};
