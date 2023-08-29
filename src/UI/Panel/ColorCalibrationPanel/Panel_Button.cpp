#include "UI/Panel/ColorCalibrationPanel/Panel_Button.hpp"

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <wx/stringimpl.h>

ColorCalibrationPanelButton::ColorCalibrationPanelButton(wxWindow *parent,
                                                         wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);
    main_status_panel = new ColorCalibrationMainStatusPanel(this);

    blue_status_panel = new BlueStatusPanel(this);
    yellow_status_panel = new YellowStatusPanel(this);

    wxStaticText *lrSpacer = new wxStaticText(
        this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10));

    wxBoxSizer *lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(blue_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);
    lrSizer->Add(lrSpacer, 0, wxEXPAND);
    lrSizer->Add(yellow_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);

    other_status_panel = new ColorCalibrationOtherPanel(this);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(other_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void ColorCalibrationPanelButton::update(const AppState &state) {
    main_status_panel->update(state);
    blue_status_panel->update(state);
    yellow_status_panel->update(state);
    other_status_panel->update(state);

    auto okState = state.colorCalibrationPanel.okButtonState;
    auto cancelState = state.colorCalibrationPanel.cancelButtonState;
    ok_cancel_panel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(ColorCalibrationPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

