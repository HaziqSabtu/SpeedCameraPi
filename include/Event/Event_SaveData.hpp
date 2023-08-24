#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_SAVE_DATA_EVENT, wxCommandEvent);

enum SAVE_DATA_EVENT_TYPE {
    SAVE_DATA_START,
    SAVE_DATA_END,
    SAVE_DATA_ERROR

};
