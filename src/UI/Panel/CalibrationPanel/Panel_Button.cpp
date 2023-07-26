#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusTool.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <wx/gtk/stattext.h>
#include <wx/stringimpl.h>

CalibrationPanelButton::CalibrationPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    cPanel = new CalibrationMainStatusPanel(this);
    ctPanel = new CalibrationToolPanel(this);
    coPanel = new CalibrationOtherPanel(this);
    okCancelPanel = new OKCancelPanel(this);

    wxStaticText *Spacer = new wxStaticText(this, wxID_ANY, wxEmptyString,
                                            wxDefaultPosition, wxDefaultSize);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(ctPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(coPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(Spacer, 1, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(okCancelPanel, 0, wxEXPAND | wxBOTTOM, 0);

    this->SetSizer(main_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CalibrationPanelButton, wxPanel)
END_EVENT_TABLE()

