#include "UI/Button/BitmapButton/Button_Accept.hpp"
#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp>

YellowStatusPanel::YellowStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::COLOR_CALIB_YELLOW_NONE) {

    color_Button = new BitmapColorPicker(this, Enum::CC_SelectYellow_Button_ID,
                                         Data::BitmapSelectYellow);
    clear_Button = new BitmapAccept(this, Enum::CC_AcceptYellow_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(color_Button, 1, wxEXPAND);
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

void YellowStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void YellowStatusPanel::update(const AppState &state) {
    // // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    setPanelState(ps.yellowStatusState);
    color_Button->update(ps.selectYellowButtonState);
    clear_Button->update(ps.acceptYellowButtonState);
}

void YellowStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CALIB_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CALIB_NONE);
    }
}