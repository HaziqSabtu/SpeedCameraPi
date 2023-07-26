#include "UI/Panel/ColorCalibrationPanel/Panel_Button.hpp"
#include "UI/Button/Button_ToggleCamera.hpp"
#include "Utils/Enum.hpp"
#include <wx/stringimpl.h>

ColorCalibrationPanelButton::ColorCalibrationPanelButton(wxWindow *parent,
                                                         wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    main_status_panel = new ColorCalibrationMainStatusPanel(this);

    left_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);
    right_Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString);

    ok_cancel_panel = new OKCancelPanel(this);

    button_sizer = new wxBoxSizer(wxVERTICAL);
    button_sizer->Add(main_status_panel, 0, wxEXPAND | wxBOTTOM, 10);
    button_sizer->Add(Spacer, 1, wxEXPAND);
    button_sizer->Add(ok_cancel_panel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(ColorCalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

