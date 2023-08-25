
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

TrimDataPanelButton::TrimDataPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

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
    button_sizer->Add(Spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(TrimDataPanelButton, wxPanel)
END_EVENT_TABLE()

