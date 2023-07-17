#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    switch_Button = new wxButton(this, Enum::CP_SWITCH_Button_ID, "Switch");
    start_Button = new ButtonToggleCam(this, Enum::CL_Start_Button_ID);
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(start_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(switch_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

