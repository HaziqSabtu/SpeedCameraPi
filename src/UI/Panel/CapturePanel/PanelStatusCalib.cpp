#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Road.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCalib.hpp>
#include <wx/sizer.h>

CalibrationStatusPanel::CalibrationStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OK) {

    calibrate_Button = new BitmapRoad(this, Enum::CP_Calibration_Button_ID);
    reset_Button = new BitmapRemove(this, Enum::CP_RemoveCalibration_Button_ID);

    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(calibrate_Button, 1, wxEXPAND);
    hSizer->Add(reset_Button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(hSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();

    // reset_Button->Bind(wxEVT_BUTTON, &CalibrationStatusPanel::OnButtonClicked,
    //                    this);
}

void CalibrationStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CalibrationStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}

void CalibrationStatusPanel::update(const AppState &state) {
    setPanelState(state.cameraPanel.calibStatusState);
    calibrate_Button->update(state.cameraPanel.calibButtonState);
    reset_Button->update(state.cameraPanel.calibRemoveButtonState);
}
