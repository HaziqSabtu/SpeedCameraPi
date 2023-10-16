#pragma once

#include <wx/event.h>

wxDECLARE_EVENT(c_REPLAY_EVENT, wxCommandEvent);

enum REPLAY_EVENT_TYPE { REPLAY_START = 1, REPLAY_END };
