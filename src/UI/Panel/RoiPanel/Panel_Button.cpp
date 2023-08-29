#include "UI/Panel/RoiPanel/Panel_Button.hpp"

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

RoiPanelButton::RoiPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    main_status_panel = new RoiMainStatusPanel(this);

    roi_tools_panel = new RoiToolsPanel(this);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(roi_tools_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void RoiPanelButton::update(const AppState &state) {
    main_status_panel->update(state);
    roi_tools_panel->update(state);

    auto okState = state.roiPanel.okButtonState;
    auto cancelState = state.roiPanel.cancelButtonState;
    ok_cancel_panel->update(okState, cancelState);
}

// clang-format off
BEGIN_EVENT_TABLE(RoiPanelButton, wxPanel)
END_EVENT_TABLE()

