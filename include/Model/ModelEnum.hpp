#pragma once

#include <wx/wx.h>

namespace ModelEnum {
enum ModelIDs {
    MODEL_START_CAPTURE = wxID_HIGHEST + 1,
    MODEL_END_CAPTURE,
    MODEL_START_PROCESSING_LOAD,
};
}