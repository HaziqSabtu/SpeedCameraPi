#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_ROI_EVENT, wxCommandEvent);

enum ROI_EVENT_TYPE {
    ROI_START = 1,
    ROI_END,
    ROI_ERROR,
};
