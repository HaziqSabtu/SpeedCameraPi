#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Road.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCalib.hpp>
#include <wx/sizer.h>

CaptureButtonCalibration::CaptureButtonCalibration(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OK) {

    Calibrate_Button = new BitmapRoad(this, Enum::CP_Calibration_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::CP_RemoveCalibration_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

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

void CaptureButtonCalibration::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonCalibration::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}

void CaptureButtonCalibration::update(const AppState &state) {
    setPanelState(state.cameraPanel.calibStatusState);
    Calibrate_Button->update(state.cameraPanel.calibButtonState);
    Reset_Button->update(state.cameraPanel.calibRemoveButtonState);
}
