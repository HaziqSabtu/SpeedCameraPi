#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_CALIBRATION_EVENT, wxCommandEvent);

enum CALIBRATION_EVENT_TYPE {
    CALIBRATION_CAMERA_START = 1,
    CALIBRATION_CAMERA_END,
    CALIBRATION_CAMERA_ERROR,

    CALIBRATION_CAPTURE_START,
    CALIBRATION_CAPTURE_END,
    CALIBRATION_CAPTURE_ERROR,

    CALIBRATION_LINE_FOUND,
    CALIBRATION_LINE_NOT_FOUND,
};
