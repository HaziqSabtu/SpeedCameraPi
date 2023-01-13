#ifndef ENUM_HPP
#define ENUM_HPP

#include <wx/wx.h>

namespace Enum {
enum ProjectIDs {

    // Notebook
    NOTEBOOK_ID = wxID_HIGHEST + 1,
    // SelectRoiPanel
    IMG_PANEL_ID,
    BUTTON_PANEL_ID,
    Next_Button_ID,
    Prev_Button_ID,
    Sel_Button_ID,
    RemoveROI_Button_ID,

    // panel2
    NEXT_PANEL_ID,
    PREV_PANEL_ID,
};
}; // namespace Enum

#endif