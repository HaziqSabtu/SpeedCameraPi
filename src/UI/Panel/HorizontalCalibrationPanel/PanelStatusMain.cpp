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
#include <UI/Panel/HorizontalCalibrationPanel/PanelStatusMain.hpp>

HorizontalCalibrationButtonMain::HorizontalCalibrationButtonMain(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_NONE) {

    CalibrateCamera_Button =
        new BitmapT2Calibration(this, Enum::HC_CalibrationCamera_Button_ID);
    CalibrateCapture_Button =
        new BitmapT2Calibration(this, Enum::HC_CalibrationCapture_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::HC_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(CalibrateCamera_Button, 1, wxEXPAND);
    buttonSizer->Add(CalibrateCapture_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);

    Reset_Button->Bind(wxEVT_BUTTON,
                       &HorizontalCalibrationButtonMain::OnButtonClicked, this);
}

void HorizontalCalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void HorizontalCalibrationButtonMain::update(const AppState &state) {
    // set panel
    HorizontalCalibrationPanelState ps = state.horizontalCalibrationPanel;
    setPanelState(ps.state);

    CalibrateCamera_Button->update(ps.calibrationButtonState);
    CalibrateCapture_Button->update(ps.calibrationCaptureButtonState);
    Reset_Button->update(ps.removeButtonState);
}

void HorizontalCalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
