#ifndef ENUM_HPP
#define ENUM_HPP

#include <wx/wx.h>

namespace Enum {
enum ProjectIDs {

    // Notebook
    NOTEBOOK_ID = wxID_HIGHEST + 1,
    // SelectRoiPanel
    SR_IMG_PANEL_ID,
    SR_BUTTON_PANEL_ID,
    SR_Next_Button_ID,
    SR_Prev_Button_ID,
    SR_Sel_Button_ID,
    SR_RemoveROI_Button_ID,
    // OpticalFlowPanel
    OF_IMG_PANEL_ID,
    OF_BUTTON_PANEL_ID,
    OF_Next_Button_ID,
    OF_Prev_Button_ID,
    OF_Sel_Button_ID,
    OF_RemoveROI_Button_ID,

    // panel2
    NEXT_PANEL_ID,
    PREV_PANEL_ID,
};
}; // namespace Enum

#endif