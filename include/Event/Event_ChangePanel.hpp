#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_CHANGE_PANEL_EVENT, wxCommandEvent);

enum CHANGE_PANEL_EVENT_TYPE { CHANGE_OK = 1, CHANGE_ERROR };
