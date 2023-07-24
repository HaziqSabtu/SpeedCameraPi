#pragma once

#include <opencv2/core.hpp>
#include <wx/rawbmp.h>
#include <wx/wx.h>

namespace Utils {
std::string wxStringToString(wxString wxstr);
bool cvMatToWxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap);
cv::Point wxPointToCvPoint(const wxPoint &point);
wxBitmap recolor(wxBitmap &b, const wxColour &c);
wxBitmap resize(const wxBitmap &b, const wxSize &s);
} // namespace Utils