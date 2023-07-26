#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    // camera_Button = new ButtonToggleCam(this, Enum::CL_ToggleCamera_Button_ID);
    // start_Button = new wxButton(this, Enum::CL_Start_Button_ID, "Start");

    // recalibrate_Button =
    //     new wxButton(this, Enum::CL_ChangeColor_Button_ID, "Recalibrate");
    // manual_Button =
    //     new wxButton(this, Enum::CL_ChangeManual_Button_ID, "Manual");

    // cancel_Button = new wxButton(this, Enum::CL_Back_Button_ID, "Cancel");
    // OK_Button = new wxButton(this, Enum::CL_OK_Button_ID, "OK");

    cPanel = new CalibrationMainStatusPanel(this);

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    // left_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);
    // right_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);

    // left_sizer = new wxBoxSizer(wxVERTICAL);
    // left_sizer->Add(camera_Button, 0, wxEXPAND | wxBOTTOM, 10);
    // left_sizer->Add(start_Button, 0, wxEXPAND | wxBOTTOM, 10);
    // left_sizer->Add(left_Spacer, 1, wxEXPAND);
    // left_sizer->Add(cancel_Button, 0, wxEXPAND | wxBOTTOM, 10);

    // right_sizer = new wxBoxSizer(wxVERTICAL);
    // right_sizer->Add(recalibrate_Button, 0, wxEXPAND | wxBOTTOM, 10);
    // right_sizer->Add(manual_Button, 0, wxEXPAND | wxBOTTOM, 10);
    // right_sizer->Add(right_Spacer, 1, wxEXPAND);
    // right_sizer->Add(OK_Button, 0, wxEXPAND | wxBOTTOM, 10);

    // button_sizer = new wxBoxSizer(wxHORIZONTAL);
    // button_sizer->Add(left_sizer, 1, wxEXPAND | wxALL, 0);
    // button_sizer->Add(Spacer, 0, wxALL, 0);
    // button_sizer->Add(right_sizer, 1, wxEXPAND | wxALL, 0);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);

    this->SetSizer(main_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

