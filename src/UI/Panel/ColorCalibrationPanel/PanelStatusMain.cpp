#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelStatusMain.hpp>

ColorCalibrationButtonMain::ColorCalibrationButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::COLOR_CALIB) {

    Calibrate_Button = new BitmapCalibration(this, Enum::CC_Start_Button_ID);
    Stop_Button = new BitmapStop(this, Enum::CC_Stop_Button_ID);
    Preview_Button =
        new BitmapT2MagnifyGlass(this, Enum::CC_ToggleCamera_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::CC_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Stop_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);

    Reset_Button->Bind(wxEVT_BUTTON,
                       &ColorCalibrationButtonMain::OnButtonClicked, this);
}

void ColorCalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ColorCalibrationButtonMain::update(const AppState &state) {
    // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    Calibrate_Button->update(ps.calibrationButtonState);
    Stop_Button->update(ps.stopButtonState);
    Preview_Button->update(ps.cameraButtonState);
    Reset_Button->update(ps.removeButtonState);
}

void ColorCalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
