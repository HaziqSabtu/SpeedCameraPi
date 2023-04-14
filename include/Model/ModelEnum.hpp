#pragma once

#include <wx/wx.h>

namespace ModelEnum {
enum ModelIDs {
    MODEL_START_CAPTURE = wxID_HIGHEST + 1,
    MODEL_END_CAPTURE,
    MODEL_START_LOADFILE,
    MODEL_END_LOADFILE,
    MODEL_START_LOADCAPTURE,
    MODEL_END_LOADCAPTURE,
};
}