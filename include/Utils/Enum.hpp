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
    SR_NextPage_Button_ID,
    // OpticalFlowPanel
    OF_IMG_PANEL_ID,
    OF_BUTTON_PANEL_ID,
    OF_Next_Button_ID,
    OF_Prev_Button_ID,
    OF_Track_Button_ID,
    OF_RemoveROI_Button_ID,
    OF_Optical_Button_ID,
    OF_Eval_Button_ID,
    OF_NextPage_Button_ID,
    // LaneDetectionPanel
    LD_IMG_PANEL_ID,
    LD_BUTTON_PANEL_ID,
    LD_Next_Button_ID,
    LD_Prev_Button_ID,
    LD_Run_Button_ID,
    LD_Left_Button_ID,
    LD_Right_Button_ID,
    LD_Both_Button_ID,
    // SelectLinePanel
    SL_IMG_PANEL_ID,
    SL_BUTTON_PANEL_ID,
    SL_BB_ID,
    SL_Canny_Button_ID,
    SL_Hough_Button_ID,
    SL_Clear_Button_ID,
    // ObjectDetectionPanel
    OD_IMG_PANEL_ID,
    OD_BUTTON_PANEL_ID,
    OD_BB_ID,
    OD_Next_Button_ID,
    OD_BBox_Button_ID,
    OD_OptF_Button_ID,
    OD_BotL_Button_ID,
    OD_Line_Button_ID,
    // panel2
    NEXT_PANEL_ID,
    PREV_PANEL_ID,
};
}; // namespace Enum

#endif