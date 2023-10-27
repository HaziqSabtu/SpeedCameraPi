#pragma once

#include <opencv2/core.hpp>

/**
 * @brief Data for Tracking Process
 *
 */
struct TrackingData {

    // The initial ROI
    cv::Rect roi;

    TrackingData();
    TrackingData(cv::Rect roi);

    void clear();
    bool isInit();

    bool operator==(const TrackingData &other) const;
    bool operator!=(const TrackingData &other) const;

    TrackingData clone() const;
    TrackingData &operator=(const TrackingData &other);
};
