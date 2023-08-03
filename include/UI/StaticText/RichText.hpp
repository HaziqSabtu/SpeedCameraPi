#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/chartype.h>
#include <wx/wx.h>

struct RichTextData {
    wxString text;
    wxColour colour;
};

typedef std::vector<RichTextData> RTD;

namespace RichTextCollection {
const RTD CALIB_NONE = {
    {wxT("Calibration: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD CALIB_OK = {
    {wxT("Calibration: "), Theme::Text},
    {wxT("CALIBRATED"), Theme::StatusOk},
};

const RTD CAPTURE_NONE = {
    {wxT("Capture: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD CAPTURE_OK = {
    {wxT("Capture: "), Theme::Text},
    {wxT("CAPTURED"), Theme::StatusOk},
};

const RTD ROI_NONE = {
    {wxT("ROI: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD ROI_OK = {
    {wxT("ROI: "), Theme::Text},
    {wxT("SET"), Theme::StatusOk},
};

const RTD DEBUG = {
    {wxT("#DEBUG"), Theme::Text},
};

const RTD LEFT_NONE = {
    {wxT("Left: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD LEFT_OK = {
    {wxT("Left: "), Theme::Text},
    {wxT("SELECTED"), Theme::StatusOk},
};

const RTD RIGHT_NONE = {
    {wxT("Right: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD RIGHT_OK = {
    {wxT("Right: "), Theme::Text},
    {wxT("SELECTED"), Theme::StatusOk},
};

const RTD CALIB_TOOL = {
    {wxT("Calibration Tool"), Theme::Text},
};

const RTD CALIB_OTHER = {
    {wxT("Others"), Theme::Text},
};

const RTD COLOR_CALIB = {
    {wxT("Color Calibration"), Theme::Text},
};

const RTD COLOR_CALIB_BLUE_NONE = {
    {wxT("Blue: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD COLOR_CALIB_BLUE_OK = {
    {wxT("Blue: "), Theme::Text},
    {wxT("CALIBRATED"), Theme::StatusOk},
};

const RTD COLOR_CALIB_YELLOW_NONE = {
    {wxT("Yellow: "), Theme::Text},
    {wxT("NONE"), Theme::StatusNone},
};

const RTD COLOR_CALIB_YELLOW_OK = {
    {wxT("Yellow: "), Theme::Text},
    {wxT("CALIBRATED"), Theme::StatusOk},
};

const RTD ROI_TOOLS = {
    {wxT("ROI Tools"), Theme::Text},
};
}; // namespace RichTextCollection