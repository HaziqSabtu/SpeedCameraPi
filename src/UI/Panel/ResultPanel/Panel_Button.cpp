#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Back.hpp>
#include <UI/Panel/ResultPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ResultPanelButton::ResultPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    main_status_panel = new ResultMainStatusPanel(this);
    preview_status_panel = new ResultPreviewStatusPanel(this);
    back_button = new BackTextButton(this, Enum::G_Cancel_Button_ID);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(preview_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(Spacer, 1, wxEXPAND);
    button_sizer->Add(back_button, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(ResultPanelButton, wxPanel)
END_EVENT_TABLE()

