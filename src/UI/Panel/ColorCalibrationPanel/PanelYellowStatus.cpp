#include "UI/Button/BitmapButton/Button_Accept.hpp"
#include "UI/Button/BitmapButton/Button_ColorPicker.hpp"
#include "UI/Button/BitmapButton/Button_Left.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp>

ColorCalibrationButtonYellow::ColorCalibrationButtonYellow(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::COLOR_CALIB_YELLOW_NONE) {

    Color_Button = new BitmapColorPicker(this, Enum::CC_SelectYellow_Button_ID,
                                         Data::BitmapSelectYellow);
    Clear_Button = new BitmapRemove(this, Enum::CC_AcceptYellow_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Color_Button, 1, wxEXPAND);
    buttonSizer->Add(Clear_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void ColorCalibrationButtonYellow::OnButtonClicked(wxCommandEvent &e) {
    e.Skip();
}

void ColorCalibrationButtonYellow::update(const AppState &state) {
    // // set panel
    ColorCalibrationPanelState ps = state.colorCalibrationPanel;

    setPanelState(ps.yellowStatusState);
    Color_Button->update(ps.selectYellowButtonState);
    Clear_Button->update(ps.acceptYellowButtonState);
}

void ColorCalibrationButtonYellow::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::COLOR_CALIB_YELLOW_OK);
        this->Show();
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::COLOR_CALIB_YELLOW_NONE);
        this->Show();
    }

    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
    }
}
