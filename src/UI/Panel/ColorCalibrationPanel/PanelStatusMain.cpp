#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelStatusMain.hpp>

ColorCalibrationButtonMain::ColorCalibrationButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::COLOR_CALIB) {

    Calibrate_Button = new BitmapT2Calibration(this, Enum::CC_Start_Button_ID);
    Preview_Button =
        new BitmapT2MagnifyGlass(this, Enum::CC_ToggleCamera_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void ColorCalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ColorCalibrationButtonMain::update(const AppState &state) {
    // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    Calibrate_Button->update(ps.calibrationButtonState);
    Preview_Button->update(ps.cameraButtonState);
}

void ColorCalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
