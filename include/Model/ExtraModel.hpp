#pragma once

#include <memory>
#include <opencv2/core/types.hpp>

#define CCModelPtr std::shared_ptr<ColorCalibExtraModel>

class ColorCalibExtraModel {
  public:
    ColorCalibExtraModel();
    ~ColorCalibExtraModel();

    ColorCalibExtraModel(const ColorCalibExtraModel &other);
    ColorCalibExtraModel clone() const;

    ColorCalibExtraModel &operator=(const ColorCalibExtraModel &other);

    bool isBlueCalibrated();
    bool isYellowCalibrated();

    void setBlueRange(std::pair<cv::Scalar, cv::Scalar> range);
    void setYellowRange(std::pair<cv::Scalar, cv::Scalar> range);

    std::pair<cv::Scalar, cv::Scalar> getBlueRange();
    std::pair<cv::Scalar, cv::Scalar> getYellowRange();

    void resetBlueRange();
    void resetYellowRange();

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
