#include "UI/Button/BitmapButton/Button_Height.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Road.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusCalib.hpp>
#include <wx/sizer.h>

CaptureButtonCalibration::CaptureButtonCalibration(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_OK) {

    Calibrate_Button = new BitmapRoad(this, Enum::CP_LaneCalibration_Button_ID);
    Reset_Button =
        new BitmapRemove(this, Enum::CP_RemoveLaneCalibration_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CaptureButtonCalibration::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonCalibration::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }
}

void CaptureButtonCalibration::update(const AppState &state) {
    setPanelState(state.capturePanel.calibStatusState);
    Calibrate_Button->update(state.capturePanel.calibButtonState);
    Reset_Button->update(state.capturePanel.calibRemoveButtonState);
}

CaptureButtonHorCalibration::CaptureButtonHorCalibration(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::HCALIB_OK) {

    Calibrate_Button =
        new BitmapHeight(this, Enum::CP_DistCalibration_Button_ID);
    Reset_Button =
        new BitmapRemove(this, Enum::CP_RemoveDistCalibration_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CaptureButtonHorCalibration::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void CaptureButtonHorCalibration::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::HCALIB_OK);
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::HCALIB_NONE);
        this->Show();
        return;
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }
}

void CaptureButtonHorCalibration::update(const AppState &state) {
    setPanelState(state.capturePanel.horCalibStatusState);
    Calibrate_Button->update(state.capturePanel.calibButtonState);
    Reset_Button->update(state.capturePanel.calibRemoveButtonState);
}
