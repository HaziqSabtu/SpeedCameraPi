#include <UI/Panel/RoiPanel/Panel_Button.hpp>

RoiButtonPanel::RoiButtonPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    switchButton = new wxButton(this, Enum::CP_SWITCH_Button_ID, "Switch");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(switchButton, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);
}

void RoiButtonPanel::DisableAllButtons() {}

void RoiButtonPanel::EnableAllButtons() {}

// clang-format off
BEGIN_EVENT_TABLE(RoiButtonPanel, wxPanel)
END_EVENT_TABLE()

