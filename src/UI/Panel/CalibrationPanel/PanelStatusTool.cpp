#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusTool.hpp>

CalibrationButtonTool::CalibrationButtonTool(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_TOOL) {

    SetPoint_Button = new BitmapTarget(this, Enum::CL_SelectPoint_Button_ID);
    Cancel_Button = new BitmapCancel(this, Enum::CL_ClearPoint_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(SetPoint_Button, 1, wxEXPAND);
    buttonSizer->Add(Cancel_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CalibrationButtonTool::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;

    setPanelState(ps.toolStatusState);

    SetPoint_Button->update(ps.selectPointButtonState);
    Cancel_Button->update(ps.cancelCalibrationButtonState);
}

void CalibrationButtonTool::setPanelState(PanelState state) {
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