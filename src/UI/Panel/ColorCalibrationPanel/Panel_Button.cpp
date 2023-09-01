#include "UI/Panel/ColorCalibrationPanel/Panel_Button.hpp"

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <wx/stringimpl.h>

ColorCalibrationPanelButton::ColorCalibrationPanelButton(wxWindow *parent,
                                                         wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);
    MainPanel = new ColorCalibrationButtonMain(this);

    BluePanel = new ColorCalibrationButtonBlue(this);
    YellowPanel = new ColorCalibrationButtonYellow(this);

    wxStaticText *lrSpacer = new wxStaticText(
        this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10));

    wxBoxSizer *lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(BluePanel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);
    lrSizer->Add(lrSpacer, 0, wxEXPAND);
    lrSizer->Add(YellowPanel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);

    OtherPanel = new ColorCalibrationButtonOther(this);

    OkCancelPanel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(OtherPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void ColorCalibrationPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    BluePanel->update(state);
    YellowPanel->update(state);
    OtherPanel->update(state);

    auto okState = state.colorCalibrationPanel.okButtonState;
    auto cancelState = state.colorCalibrationPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(ColorCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

