#ifndef ENUM_HPP
#define ENUM_HPP

#include <wx/wx.h>

namespace Enum {
enum ProjectIDs {

    // Notebook
    NOTEBOOK_ID = wxID_HIGHEST + 1,

    //Global
    G_Exit_Button_ID,
    G_Setting_Button_ID,
    G_Info_Button_ID,
    G_OK_Button_ID,
    G_Cancel_Button_ID,
    G_Reset_Button_ID,
    G_Plus_Button_ID,
    G_Minus_Button_ID,
    G_Toggle_Button_ID,

    // CameraPanel
    CP_Panel_ID,
    CP_IMG_PANEL_ID,
    CP_Button_Panel_ID,
    CP_Capture_Button_ID,
    CP_Stop_Button_ID,
    CP_ToggleCamera_Button_ID,
    CP_Load_Button_ID,
    CP_Camera_Button_ID,
    CP_Camera_Button2_ID,
    CP_ClearCapture_Button_ID,
    CP_Measure_Button_ID,
    CP_Calibration_Button_ID,
    CP_RemoveCalibration_Button_ID,
    CP_Roi_Button_ID,
    CP_RemoveRoi_Button_ID,
    CP_Save_Button_ID,
    CP_Trim_Button_ID,
    CP_Reset_Button_ID,

    // CalibrationPanel
    CL_CalibrationCamera_Button_ID,
    CL_CalibrationCapture_Button_ID,
    CL_ClearCalibration_Button_ID,
    CL_PreviewCamera_Button_ID,
    CL_PreviewCapture_Button_ID,
    CL_SelectPoint_Button_ID,
    CL_ClearPoint_Button_ID,
    CL_SaveCalibration_Button_ID,
    CL_CancelCalibration_Button_ID,
    CL_ChangeManual_Button_ID,
    CL_ChangeColor_Button_ID,

    // ManualCalibrationPanel
    MC_CalibrationCamera_Button_ID,
    MC_CalibrationCapture_Button_ID,
    MC_Remove_Button_ID,
    MC_PreviewCamera_Button_ID,
    MC_PreviewCapture_Button_ID,
    MC_SelectLeft_Button_ID,
    MC_RemoveLeft_Button_ID,
    MC_SelectRight_Button_ID,
    MC_RemoveRight_Button_ID,

    // ColorCalibrationPanel
    CC_Start_Button_ID,
    CC_Stop_Button_ID,
    CC_ToggleCamera_Button_ID,
    CC_Remove_Button_ID,
    CC_SelectBlue_Button_ID,
    CC_AcceptBlue_Button_ID,
    CC_SelectYellow_Button_ID,
    CC_AcceptYellow_Button_ID,
    CC_Save_Button_ID,
    CC_Restore_Button_ID,

    // RoiPanel
    RO_Panel_ID,
    RO_IMG_PANEL_ID,
    RO_Calibration_Button_ID,
    RO_Start_Button_ID,
    RO_Stop_Button_ID,
    RO_Preview_Button_ID,
    RO_Remove_Button_ID,
    RO_AcceptRect_Button_ID,
    RO_RemoveRect_Button_ID,

    // TrimPanel
    TR_Panel_ID,
    TR_IMG_PANEL_ID,
    TR_BUTTON_PANEL_ID,

    TD_Start_Button_ID,
    TD_Preview_Button_ID,
    TD_Range_Button_ID,
    TD_Reset_Button_ID,

    TD_IncrementStart_Button_ID,
    TD_DecrementStart_Button_ID,
    TD_IncrementEnd_Button_ID,
    TD_DecrementEnd_Button_ID,

    // ResultPanel
    RE_Panel_ID,
    RE_IMG_PANEL_ID,
    RE_BUTTON_PANEL_ID,
    RE_Start_Button_ID,
    RE_Redundant_Button_ID,
    RE_Preview_Button_ID,
    RE_Box_Button_ID,
    RE_Lines_Button_ID,
    RE_Lanes_Button_ID,
    RE_Replay_Button_ID,

    // SettingsPanel
    SE_Upper_HSV_ID,
    SE_Lower_HSV_ID,

    // CameraPanel->Hough
    CP_BUTTON_PANEL_HOUGH_ID,
    CP_Canny_Button_ID,
    CP_Hough_Button_ID,
    CP_Clear_Button_ID,
    CP_Next_Button_ID,
    CP_Prev_Button_ID,

    // CameraPanel->Result
    CP_BUTTON_PANEL_RESULT_ID,
    CP_Replay_Button_ID,
    CP_BBox_Button_ID,
    CP_OptF_Button_ID,
    CP_BotL_Button_ID,
    CP_SelL_Button_ID,
    CP_Reselect_Button_ID,

    // SelectLinePanel
    SL_Panel_ID,
    SL_IMG_PANEL_ID,
    SL_BUTTON_PANEL_ID,
    SL_BITMAP_ID,
    SL_Next_Button_ID,
    SL_Prev_Button_ID,
    SL_Canny_Button_ID,
    SL_Hough_Button_ID,
    SL_Clear_Button_ID,

    // ObjectDetectionPanel / Result Panel
    OD_Panel_ID,
    OD_IMG_PANEL_ID,
    OD_BUTTON_PANEL_ID,
    OD_BITMAP_ID,
    OD_Replay_Button_ID,
    OD_BBox_Button_ID,
    OD_OptF_Button_ID,
    OD_BotL_Button_ID,
    OD_Line_Button_ID,
    OD_Speed_Button_ID,

    // * old Enum Panel
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
    // panel2
    NEXT_PANEL_ID,
    PREV_PANEL_ID,
    P2_C_Button_ID,
    P2_S_Button_ID,
    // CaptureViewPanel
    CV_Panel_ID,
    CV_IMG_PANEL_ID,
    CV_BUTTON_PANEL_ID,
    CV_Next_Button_ID,
    CV_Prev_Button_ID,
};
}; // namespace Enum

#endif