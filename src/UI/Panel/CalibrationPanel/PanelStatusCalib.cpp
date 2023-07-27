#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusCalib.hpp>

CalibrationMainStatusPanel::CalibrationMainStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_NONE) {

    calibrate_Button = new BitmapCalibration(this, Enum::CL_Start_Button_ID);
    reset_Button = new BitmapRemove(this, Enum::CL_ClearCalibration_Button_ID);
    camera_Button = new BitmapT2Camera(this, Enum::CL_ToggleCamera_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(camera_Button, 1, wxEXPAND);
    buttonSizer->Add(reset_Button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
}

void CalibrationMainStatusPanel::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void CalibrationMainStatusPanel::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;
    setPanelState(ps.state);

    calibrate_Button->update(ps.calibrationButtonState);
    camera_Button->update(ps.cameraButtonState);
    reset_Button->update(ps.removeButtonState);
}

void CalibrationMainStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CAPTURE_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CAPTURE_NONE);
    }
}
