#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include <Model/AppState.hpp>
#include <UI/Button/BitmapButton/Bitmap_Calibration.hpp>
#include <UI/Button/BitmapButton/Button_Manual.hpp>
#include <UI/Button/BitmapButton/Button_Remove.hpp>
#include <UI/Button/BitmapButton/Button_User.hpp>
#include <UI/Button/BitmapButton/Type2/Button_Auto.hpp>
#include <UI/Button/BitmapButton/Type2/Button_Calibration.hpp>
#include <UI/Button/BitmapButton/Type2/Button_Camera.hpp>
#include <UI/Panel/CalibrationPanel/PanelStatusMain.hpp>
#include <UI/Panel/Common/TextOutlinePanel.hpp>
#include <UI/StaticText/RichText.hpp>
#include <Utils/Enum.hpp>

CalibrationButtonMain::CalibrationButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_NONE) {

    Calibrate_Button = new BitmapT2Auto(this, Enum::CL_Calibration_Button_ID);
    Preview_Button = new BitmapT2MagnifyGlass(this, Enum::CL_Preview_Button_ID);
    ManualCalibration_Button =
        new BitmapManual(this, Enum::CL_ChangeManual_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::CL_ClearCalibration_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(ManualCalibration_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CalibrationButtonMain::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;
    setPanelState(ps.state);

    Calibrate_Button->update(ps.calibrationButtonState);
    Preview_Button->update(ps.previewButtonState);
    ManualCalibration_Button->update(ps.manualCalibrationButtonState);

    Reset_Button->update(ps.removeButtonState);
}

void CalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CAPTURE_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CAPTURE_NONE);
    }
}
