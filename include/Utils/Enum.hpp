#ifndef ENUM_HPP
#define ENUM_HPP

#include <wx/wx.h>

namespace Enum {
enum ProjectIDs {
    // SelectRoiPanel
    IMG_PANEL_ID = wxID_HIGHEST + 1,
    BUTTON_PANEL_ID,
    Next_Button_ID,
    Prev_Button_ID,
    Sel_Button_ID,
    RemoveROI_Button_ID,
};
}; // namespace Enum

#endif