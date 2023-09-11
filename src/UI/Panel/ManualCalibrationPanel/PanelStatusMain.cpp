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
#include <UI/Panel/ManualCalibrationPanel/PanelStatusMain.hpp>

ManualCalibrationButtonMain::ManualCalibrationButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CALIB_NONE) {

    CalibrateCamera_Button =
        new BitmapT2Calibration(this, Enum::MC_CalibrationCamera_Button_ID);
    CalibrateCapture_Button =
        new BitmapT2Calibration(this, Enum::MC_CalibrationCapture_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::MC_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(CalibrateCamera_Button, 1, wxEXPAND);
    buttonSizer->Add(CalibrateCapture_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

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

    Reset_Button->Bind(wxEVT_BUTTON,
                       &ManualCalibrationButtonMain::OnButtonClicked, this);
}

void ManualCalibrationButtonMain::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ManualCalibrationButtonMain::update(const AppState &state) {
    // set panel
    ManualCalibrationPanelState ps = state.manualCalibrationPanel;
    setPanelState(ps.state);

    CalibrateCamera_Button->update(ps.calibrationButtonState);
    CalibrateCapture_Button->update(ps.calibrationCaptureButtonState);
    Reset_Button->update(ps.removeButtonState);
}

void ManualCalibrationButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
