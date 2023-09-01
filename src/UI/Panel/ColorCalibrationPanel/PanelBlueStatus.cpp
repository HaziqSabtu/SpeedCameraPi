#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/Button_Accept.hpp"
#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelBlueStatus.hpp>

ColorCalibrationButtonBlue::ColorCalibrationButtonBlue(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::COLOR_CALIB_BLUE_NONE) {

    Color_Button = new BitmapColorPicker(this, Enum::CC_SelectBlue_Button_ID,
                                         Data::BitmapSelectBlue);
    Clear_Button = new BitmapAccept(this, Enum::CC_AcceptBlue_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Color_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

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

void ColorCalibrationButtonBlue::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ColorCalibrationButtonBlue::update(const AppState &state) {
    // // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    setPanelState(ps.blueStatusState);
    Color_Button->update(ps.selectBlueButtonState);
    Clear_Button->update(ps.acceptBlueButtonState);
}

void ColorCalibrationButtonBlue::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}
