#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Back.hpp>
#include <UI/Panel/ResultPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ResultPanelButton::ResultPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    main_status_panel = new ResultMainStatusPanel(this);
    preview_status_panel = new ResultPreviewStatusPanel(this);
    back_button = new BackTextButton(this, Enum::G_Cancel_Button_ID);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(preview_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(back_button, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void ResultPanelButton::update(const AppState &state) {
    main_status_panel->update(state);
    preview_status_panel->update(state);
}

// clang-format off
BEGIN_EVENT_TABLE(ResultPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

