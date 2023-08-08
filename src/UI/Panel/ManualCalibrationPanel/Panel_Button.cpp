
#include "Utils/Enum.hpp"
#include <UI/Panel/ManualCalibrationPanel/Panel_Button.hpp>
#include <wx/stringimpl.h>

ManualCalibrationPanelButton::ManualCalibrationPanelButton(wxWindow *parent,
                                                           wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    main_status_panel = new ManualCalibrationMainStatusPanel(this);

    left_status_panel = new LeftStatusPanel(this);
    right_status_panel = new RightStatusPanel(this);

    lrSizer = new wxBoxSizer(wxHORIZONTAL);
    lrSizer->Add(left_status_panel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    lrSizer->Add(right_status_panel, 1, wxEXPAND | wxBOTTOM, 10);

    preview_panel = new ManualCalibrationPreviewPanel(this);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(lrSizer, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(preview_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(Spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(ManualCalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

