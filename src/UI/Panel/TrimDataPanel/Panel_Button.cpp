
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

TrimDataPanelButton::TrimDataPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);
    MainPanel = new TrimButtonMain(this);

    SetStartPanel = new TrimButtonSetStart(this);
    SetEndPanel = new TrimButtonSetEnd(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(SetStartPanel, 1, wxEXPAND | wxBOTTOM, 10);
    lrSizer->AddSpacer(10);
    lrSizer->Add(SetEndPanel, 1, wxEXPAND | wxBOTTOM, 10);

    OkCancelPanel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void TrimDataPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    SetStartPanel->update(state);
    SetEndPanel->update(state);

    auto okState = state.trimDataPanel.okButtonState;
    auto cancelState = state.trimDataPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(TrimDataPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

