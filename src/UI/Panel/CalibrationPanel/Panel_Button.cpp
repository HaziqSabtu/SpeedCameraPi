#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {
    switch_Button = new wxButton(this, Enum::CP_SWITCH_Button_ID, "Switch");
    start_Button = new ButtonToggleCam(this, Enum::CL_Start_Button_ID);
    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20));

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(start_Button, 0, wxEXPAND | wxBOTTOM, 10);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(switch_Button, 0, wxEXPAND | wxBOTTOM, 10);

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(left_sizer, 1, wxALL, 0);
    button_sizer->Add(Spacer, 0, wxALL, 0);
    button_sizer->Add(right_sizer, 1, wxALL, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

