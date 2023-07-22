#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ManualCalibrationPanelButton::ManualCalibrationPanelButton(wxWindow *parent,
                                                           wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    camera_Button = new ButtonToggleCam(this, Enum::CL_ToggleCamera_Button_ID);

    cancel_Button = new wxButton(this, Enum::CL_Back_Button_ID, "Cancel");
    OK_Button = new wxButton(this, Enum::CL_OK_Button_ID, "OK");

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    main_status_panel = new ManualCalibrationMainStatusPanel(this);

    left_status_panel = new LeftStatusPanel(this);
    right_status_panel = new RightStatusPanel(this);
    wxStaticText *lrSpacer = new wxStaticText(
        this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(10, 10));

    wxBoxSizer *lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);
    lrSizer->Add(lrSpacer, 0, wxEXPAND);
    lrSizer->Add(right_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 0);

    left_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);
    right_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);

    okSizer = new wxBoxSizer(wxHORIZONTAL);
    okSizer->Add(OK_Button, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    okSizer->Add(cancel_Button, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    okSizer->Add(camera_Button, 1, wxEXPAND | wxBOTTOM, 10);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(Spacer, 1, wxEXPAND);
    button_sizer->Add(okSizer, 0, wxEXPAND | wxALL, 10);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(ManualCalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

