#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_REQUEST_UPDATE_STATE_EVENT, wxCommandEvent);

enum REQUEST_UPDATE_STATE_TYPE { REQUEST_UPDATE_STATE = 1 };
