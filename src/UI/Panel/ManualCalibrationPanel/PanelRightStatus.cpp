#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Right.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp>

RightStatusPanel::RightStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RIGHT_NONE) {

    right_Button = new BitmapR(this, Enum::MC_SelectRight_Button_ID);
    clear_Button = new BitmapRemove(this, Enum::MC_RemoveRight_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(right_Button, 1, wxEXPAND);
    buttonSizer->Add(clear_Button, 1, wxEXPAND);

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

void RightStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void RightStatusPanel::update(const AppState &state) {
    // set panel
    ManualCalibrationPanelState ps = state.manualCalibrationPanel;

    setPanelState(ps.rightStatusState);
    right_Button->update(ps.selectRightButtonState);
    clear_Button->update(ps.removeRightButtonState);
}

void RightStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
