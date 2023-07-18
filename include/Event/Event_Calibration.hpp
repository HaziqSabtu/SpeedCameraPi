#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_CALIBRATION_EVENT, wxCommandEvent);

enum CALIBRATION_EVENT_TYPE { CALIBRATION_START = 1, CALIBRATION_END };
