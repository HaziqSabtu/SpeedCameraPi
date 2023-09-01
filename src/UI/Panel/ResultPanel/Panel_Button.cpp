#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/Spacer.hpp"
#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Back.hpp>
#include <UI/Panel/ResultPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ResultPanelButton::ResultPanelButton(wxWindow *parent, wxWindowID id)
    : BaseButtonPanel(parent, id) {

    spacer = new Spacer(this);

    MainPanel = new ResultPanelMain(this);
    PreviewPanel = new ResultPanelPreview(this);
    Back_button = new BackTextButton(this, Enum::G_Cancel_Button_ID);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(MainPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(PreviewPanel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(spacer, 1, wxEXPAND);
    button_sizer->Add(Back_button, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

void ResultPanelButton::update(const AppState &state) {
    MainPanel->update(state);
    PreviewPanel->update(state);
}

// clang-format off
BEGIN_EVENT_TABLE(ResultPanelButton, BaseButtonPanel)
END_EVENT_TABLE()

