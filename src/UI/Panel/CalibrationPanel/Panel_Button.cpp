#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    camera_Button = new ButtonToggleCam(this, Enum::CL_ToggleCamera_Button_ID);
    start_Button = new wxButton(this, Enum::CL_Start_Button_ID, "Start");

    recalibrate_Button = new wxButton(this, wxID_ANY, "Recalibrate");
    manual_Button = new wxButton(this, wxID_ANY, "Manual");

    cancel_Button = new wxButton(this, Enum::CL_Back_Button_ID, "Cancel");
    OK_Button = new wxButton(this, Enum::CL_OK_Button_ID, "OK");

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20));

    left_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);
    right_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(camera_Button, 0, wxEXPAND | wxBOTTOM, 10);
    left_sizer->Add(start_Button, 0, wxEXPAND | wxBOTTOM, 10);
    left_sizer->Add(left_Spacer, 1, wxEXPAND);
    left_sizer->Add(cancel_Button, 0, wxEXPAND | wxBOTTOM, 10);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(recalibrate_Button, 0, wxEXPAND | wxBOTTOM, 10);
    right_sizer->Add(manual_Button, 0, wxEXPAND | wxBOTTOM, 10);
    right_sizer->Add(right_Spacer, 1, wxEXPAND);
    right_sizer->Add(OK_Button, 0, wxEXPAND | wxBOTTOM, 10);

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(left_sizer, 1, wxEXPAND | wxALL, 0);
    button_sizer->Add(Spacer, 0, wxALL, 0);
    button_sizer->Add(right_sizer, 1, wxEXPAND | wxALL, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

