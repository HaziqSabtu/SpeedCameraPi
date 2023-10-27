#pragma once

#include "Utils/Config/ConfigStruct.hpp"
#include <opencv2/core.hpp>
#include <wx/rawbmp.h>
#include <wx/wx.h>

namespace Utils {

/**
 * @brief Convert wxString to std::string
 *
 * @param wxstr wxString to be converted
 * @return std::string converted string
 */
std::string wxStringToString(wxString wxstr);

/**
 * @brief Convert cv::Mat to wxBitmap
 *
 * @param matBitmap source cv::Mat
 * @param bitmap destination wxBitmap
 * @return true if ok
 * @return false if not ok
 */
bool cvMatToWxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);

/**
 * @brief Convert wxPoint to cv::Point
 *
 * @param point wxPoint to be converted
 * @return cv::Point converted point
 */
cv::Point wxPointToCvPoint(const wxPoint &point);

/**
 * @brief Recolor wxBitmap
 *
 * @param b the bitmap to be recolored
 * @param c the color to be used
 * @return wxBitmap recolored bitmap
 */
wxBitmap recolor(wxBitmap &b, const wxColour &c);

/**
 * @brief Resize wxBitmap
 *
 * @param b the bitmap to be resized
 * @param s the size to be used
 * @return wxBitmap resized bitmap
 */
wxBitmap resize(const wxBitmap &b, const wxSize &s);

/**
 * @brief Convert cv::Scalar to HSVRangeConfig
 *
 * @param range cv::Scalar to be converted
 * @return std::pair<cv::Scalar, cv::Scalar> converted range
 */
std::pair<cv::Scalar, cv::Scalar>
HSVRangeConfigToScalar(const HSVRangeConfig &range);

/**
 * @brief Convert HSVRangeConfig to cv::Scalar
 *
 * @param range HSVRangeConfig to be converted
 * @return std::pair<cv::Scalar, cv::Scalar> converted range
 */
HSVRangeConfig
ScalarToHSVRangeConfig(const std::pair<cv::Scalar, cv::Scalar> &range);

wxString idToFileName(std::string id);
} // namespace Utils