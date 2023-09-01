#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusTool.hpp>

CalibrationToolPanel::CalibrationToolPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_TOOL) {

    target_button = new BitmapTarget(this, Enum::CL_SelectPoint_Button_ID);
    cancel_button = new BitmapCancel(this, Enum::CL_ClearPoint_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(target_button, 1, wxEXPAND);
    buttonSizer->Add(cancel_button, 1, wxEXPAND);

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

void CalibrationToolPanel::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;

    setPanelState(ps.toolStatusState);

    target_button->update(ps.selectPointButtonState);
    cancel_button->update(ps.cancelCalibrationButtonState);
    // ok_button->update(ps.acceptCalibrationButtonState);
}

void CalibrationToolPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    if (state == PanelState::PANEL_OK) {
        this->Show();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}