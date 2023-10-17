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
    G_SwitchMode_Button_ID,
    G_OK_Button_ID,
    G_Cancel_Button_ID,
    G_Reset_Button_ID,
    G_Plus_Button_ID,
    G_Minus_Button_ID,
    G_Toggle_Button_ID,

    // CapturePanel
    CP_Panel_ID,
    CP_Button_Panel_ID,
    CP_Capture_Button_ID,
    CP_Load_Button_ID,
    CP_Replay_Button_ID,
    CP_ClearCapture_Button_ID,
    CP_ToggleCamera_Button_ID,
    CP_LaneCalibration_Button_ID,
    CP_RemoveLaneCalibration_Button_ID,
    CP_DistCalibration_Button_ID,
    CP_RemoveDistCalibration_Button_ID,
    CP_Roi_Button_ID,
    CP_RemoveRoi_Button_ID,
    CP_Save_Button_ID,
    CP_Trim_Button_ID,
    CP_Reset_Button_ID,
    CP_Measure_Button_ID,

    // LaneCalibrationPanel
    LC_Panel_ID,
    LC_Button_Panel_ID,
    LC_Calibration_Button_ID,
    LC_Preview_Button_ID,
    LC_ChangeManual_Button_ID,
    LC_ClearCalibration_Button_ID,
    LC_SelectPoint_Button_ID,
    LC_ClearPoint_Button_ID,
    LC_SaveCalibration_Button_ID,
    LC_CancelCalibration_Button_ID,
    LC_ChangeColor_Button_ID,

    // LaneManualCalibrationPanel
    LM_Panel_ID,
    LM_Button_Panel_ID,
    LM_Calibration_Button_ID,
    LM_Remove_Button_ID,
    LM_Preview_Button_ID,
    LM_SelectLeft_Button_ID,
    LM_RemoveLeft_Button_ID,
    LM_SelectRight_Button_ID,
    LM_RemoveRight_Button_ID,

    // DistanceCalibrationPanel
    DC_Panel_ID,
    DC_Button_Panel_ID,
    DC_Calibration_Button_ID,
    DC_Preview_Button_ID,
    DC_Remove_Button_ID,
    DC_SelectBottom_Button_ID,
    DC_RemoveBottom_Button_ID,
    DC_SelectTop_Button_ID,
    DC_RemoveTop_Button_ID,

    // ColorCalibrationPanel
    CC_Panel_ID,
    CC_Button_Panel_ID,
    CC_Start_Button_ID,
    CC_Stop_Button_ID,
    CC_ToggleCamera_Button_ID,
    CC_SelectBlue_Button_ID,
    CC_AcceptBlue_Button_ID,
    CC_SelectYellow_Button_ID,
    CC_AcceptYellow_Button_ID,
    CC_Restore_Button_ID,

    // RoiPanel
    RO_Panel_ID,
    RO_Button_Panel_ID,
    RO_Calibration_Button_ID,
    RO_Start_Button_ID,
    RO_Stop_Button_ID,
    RO_Preview_Button_ID,
    RO_Remove_Button_ID,
    RO_AcceptRect_Button_ID,
    RO_RemoveRect_Button_ID,

    // TrimPanel
    TR_Panel_ID,
    TR_Button_Panel_ID,
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
    RE_Button_Panel_ID,
    RE_Start_OF_Button_ID,
    RE_Redundant_Button_ID,
    RE_Preview_Button_ID,
    RE_Box_Button_ID,
    RE_Lines_Button_ID,
    RE_Lanes_Button_ID,
    RE_Replay_Button_ID,

    // SettingsPanel
    SE_Upper_HSV_ID,
    SE_Lower_HSV_ID,

};
}; // namespace Enum

#endif