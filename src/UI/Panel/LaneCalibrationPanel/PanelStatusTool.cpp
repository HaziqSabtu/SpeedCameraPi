#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneCalibrationPanel/PanelStatusTool.hpp>

LaneCalibrationButtonTool::LaneCalibrationButtonTool(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_TOOL) {

    SetPoint_Button = new BitmapTarget(this, Enum::LC_SelectPoint_Button_ID);
    Cancel_Button = new BitmapCancel(this, Enum::LC_ClearPoint_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(SetPoint_Button, 1, wxEXPAND);
    buttonSizer->Add(Cancel_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void LaneCalibrationButtonTool::update(const AppState &state) {
    LaneCalibrationPanelState ps = state.laneCalibrationPanel;

    setPanelState(ps.toolStatusState);
    SetPoint_Button->update(ps.selectPointButtonState);
    Cancel_Button->update(ps.cancelCalibrationButtonState);
}

void LaneCalibrationButtonTool::setPanelState(PanelState state) {
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