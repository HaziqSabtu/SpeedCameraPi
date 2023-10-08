#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_SWITCH_MODE_EVENT, wxCommandEvent);

enum SWITCH_MODE_EVENT_TYPE {
    SWITCH_MODE_OK,
    SWITCH_MODE_CANCEL,
    SWITCH_MODE_ERROR
};
