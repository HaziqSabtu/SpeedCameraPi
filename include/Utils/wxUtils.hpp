#pragma once

#include "Utils/Config/ConfigStruct.hpp"
#include <opencv2/core.hpp>
#include <wx/rawbmp.h>
#include <wx/wx.h>

namespace Utils {
std::string wxStringToString(wxString wxstr);
bool cvMatToWxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);
cv::Point wxPointToCvPoint(const wxPoint &point);
wxBitmap recolor(wxBitmap &b, const wxColour &c);
wxBitmap resize(const wxBitmap &b, const wxSize &s);
std::pair<cv::Scalar, cv::Scalar>
HSVRangeConfigToScalar(const HSVRangeConfig &range);
HSVRangeConfig
ScalarToHSVRangeConfig(const std::pair<cv::Scalar, cv::Scalar> &range);
} // namespace Utils