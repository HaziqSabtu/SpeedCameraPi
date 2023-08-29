
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

TrimDataPanelButton::TrimDataPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);
    main_status_panel = new TrimDataMainPanel(this);

    set_start_panel = new SetStartPanel(this);
    set_end_panel = new SetEndPanel(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(set_start_panel, 1, wxEXPAND | wxBOTTOM, 10);
    lrSizer->AddSpacer(10);
    lrSizer->Add(set_end_panel, 1, wxEXPAND | wxBOTTOM, 10);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void TrimDataPanelButton::update(const AppState &state) {
    main_status_panel->update(state);
    set_start_panel->update(state);
    set_end_panel->update(state);

    auto okState = state.trimDataPanel.okButtonState;
    auto cancelState = state.trimDataPanel.cancelButtonState;
    ok_cancel_panel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(TrimDataPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

