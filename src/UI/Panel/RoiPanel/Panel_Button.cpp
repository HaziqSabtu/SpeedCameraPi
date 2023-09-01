#include "UI/Panel/RoiPanel/Panel_Button.hpp"

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

RoiPanelButton::RoiPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    MainPanel = new RoiButtonMain(this);

    ToolsPanel = new RoiButtonTools(this);

    OkCancelPanel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(ToolsPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(OkCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void RoiPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    ToolsPanel->update(state);

    auto okState = state.roiPanel.okButtonState;
    auto cancelState = state.roiPanel.cancelButtonState;
    OkCancelPanel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(RoiPanelButton, wxPanel)
END_EVENT_TABLE()

