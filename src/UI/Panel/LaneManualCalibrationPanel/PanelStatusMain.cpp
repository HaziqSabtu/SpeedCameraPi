#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneManualCalibrationPanel/PanelStatusMain.hpp>

LaneManualCalibrationButtonMain::LaneManualCalibrationButtonMain(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_NONE) {

    Calibrate_Button =
        new BitmapT2Calibration(this, Enum::LM_Calibration_Button_ID);
    Preview_Button = new BitmapT2MagnifyGlass(this, Enum::LM_Preview_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::LM_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);

    Reset_Button->Bind(wxEVT_BUTTON,
                       &LaneManualCalibrationButtonMain::OnButtonClicked, this);
}

void LaneManualCalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void LaneManualCalibrationButtonMain::update(const AppState &state) {
    // set panel
    LaneManualCalibrationPanelState ps = state.laneManualCalibrationPanel;
    setPanelState(ps.state);

    Calibrate_Button->update(ps.calibrationButtonState);
    Preview_Button->update(ps.previewButtonState);
    Reset_Button->update(ps.removeButtonState);
}

void LaneManualCalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
