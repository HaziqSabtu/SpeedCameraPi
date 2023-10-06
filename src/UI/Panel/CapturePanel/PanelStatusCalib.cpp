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

    SetButtonSizer(buttonSizer);
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
