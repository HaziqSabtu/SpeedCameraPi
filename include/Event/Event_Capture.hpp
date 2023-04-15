
#ifndef CAPTURE_EVENT_HPP
#define CAPTURE_EVENT_HPP

#include <wx/event.h>

wxDECLARE_EVENT(c_CAPTURE_EVENT, wxCommandEvent);

enum CAPTURE_EVENT_TYPE { CAPTURE_START = 1, CAPTURE_END };

#endif