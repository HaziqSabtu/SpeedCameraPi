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
const RTD CALIB_NONE = {{wxT("Calibration: "), Theme::Text},
                        {wxT("NONE"), Theme::StatusNone}};

const RTD CALIB_OK = {{wxT("Calibration: "), Theme::Text},
                      {wxT("CALIBRATED"), Theme::StatusOk}};

const RTD CAPTURE_NONE = {{wxT("Capture: "), Theme::Text},
                          {wxT("NONE"), Theme::StatusNone}};

const RTD CAPTURE_OK = {{wxT("Capture: "), Theme::Text},
                        {wxT("CAPTURED"), Theme::StatusOk}};

const RTD ROI_NONE = {{wxT("ROI: "), Theme::Text},
                      {wxT("NONE"), Theme::StatusNone}};

const RTD ROI_OK = {{wxT("ROI: "), Theme::Text}, {wxT("SET"), Theme::StatusOk}};

const RTD DEBUG = {{wxT("#DEBUG"), Theme::Text}};

const RTD LEFT_NONE = {{wxT("Left: "), Theme::Text},
                       {wxT("NONE"), Theme::StatusNone}};

const RTD LEFT_OK = {{wxT("Left: "), Theme::Text},
                     {wxT("SELECTED"), Theme::StatusOk}};

const RTD RIGHT_NONE = {{wxT("Right: "), Theme::Text},
                        {wxT("NONE"), Theme::StatusNone}};

const RTD RIGHT_OK = {{wxT("Right: "), Theme::Text},
                      {wxT("SELECTED"), Theme::StatusOk}};
}; // namespace RichTextCollection