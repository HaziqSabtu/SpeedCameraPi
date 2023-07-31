#pragma once

#include <opencv2/core/types.hpp>

#define CCModelPtr std::shared_ptr<ColorCalibExtraModel>

class ColorCalibExtraModel {
  public:
    ColorCalibExtraModel() {
        lower_blue = DEF_lower_blue;
        upper_blue = DEF_upper_blue;
        lower_yellow = DEF_lower_yellow;
        upper_yellow = DEF_upper_yellow;
    };

    ~ColorCalibExtraModel() {};

    ColorCalibExtraModel(const ColorCalibExtraModel &other) {
        lower_blue = other.lower_blue;
        upper_blue = other.upper_blue;
        lower_yellow = other.lower_yellow;
        upper_yellow = other.upper_yellow;
    }

    ColorCalibExtraModel clone() const { return ColorCalibExtraModel(*this); }

    // Copy assignment operator (deep copy)
    ColorCalibExtraModel &operator=(const ColorCalibExtraModel &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        lower_blue = other.lower_blue;
        upper_blue = other.upper_blue;
        lower_yellow = other.lower_yellow;
        upper_yellow = other.upper_yellow;

        return *this;
    }

    bool isBlueCalibrated() {
        return lower_blue != cv::Scalar(0, 0, 0) &&
               upper_blue != cv::Scalar(0, 0, 0);
    }

    bool isYellowCalibrated() {
        return lower_yellow != cv::Scalar(0, 0, 0) &&
               upper_yellow != cv::Scalar(0, 0, 0);
    }

    void setBlueRange(std::pair<cv::Scalar, cv::Scalar> range) {
        lower_blue = range.first;
        upper_blue = range.second;
    }

    void setYellowRange(std::pair<cv::Scalar, cv::Scalar> range) {
        lower_yellow = range.first;
        upper_yellow = range.second;
    }

    std::pair<cv::Scalar, cv::Scalar> getBlueRange() {
        return std::make_pair(lower_blue, upper_blue);
    }

    std::pair<cv::Scalar, cv::Scalar> getYellowRange() {
        return std::make_pair(lower_yellow, upper_yellow);
    }

    void resetBlueRange() {
        lower_blue = DEF_lower_blue;
        upper_blue = DEF_upper_blue;
    }

    void resetYellowRange() {
        lower_yellow = DEF_lower_yellow;
        upper_yellow = DEF_upper_yellow;
    }

  private:
    const cv::Scalar DEF_lower_blue = cv::Scalar(0, 0, 0);
    const cv::Scalar DEF_upper_blue = cv::Scalar(0, 0, 0);

    const cv::Scalar DEF_lower_yellow = cv::Scalar(0, 0, 0);
    const cv::Scalar DEF_upper_yellow = cv::Scalar(0, 0, 0);

    cv::Scalar lower_blue;
    cv::Scalar upper_blue;

    cv::Scalar lower_yellow;
    cv::Scalar upper_yellow;
};