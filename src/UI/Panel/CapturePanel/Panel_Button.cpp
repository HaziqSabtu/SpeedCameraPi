#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/CapturePanel/PanelStatusDebug.hpp"
#include "UI/Panel/Common/DividerPanel.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/Theme/Theme.hpp"
#include <UI/Panel/CapturePanel/Panel_Button.hpp>
#include <wx/gdicmn.h>
#include <wx/layout.h>

CaptureButtonPanel::CaptureButtonPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id, wxDefaultPosition, wxSize(400, 400)) {

    switch_Button = new DefaultButton(
        this, Enum::CP_SWITCH_Button_ID, "Measure", Theme::Primary,
        Theme::StatusText, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    switch_Button->SetFont(
        wxFontInfo(20).Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Bold());

    Spacer =
        new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

    cPanel = new CaptureStatusPanel(this);
    csPanel = new CalibrationStatusPanel(this);
    rPanel = new ROIStatusPanel(this);
    dPanel = new DebugStatusPanel(this);
    dPanel->ToggleCamera_Button->SetBackgroundColour(wxColour(225, 232, 237));
    // dPanel->ToggleCamera_Button->SetBackgroundColour(wxColour(245, 248, 250));

    left_sizer = new wxBoxSizer(wxVERTICAL);
    left_sizer->Add(csPanel, 0, wxEXPAND | wxBOTTOM, 0);

    right_sizer = new wxBoxSizer(wxVERTICAL);
    right_sizer->Add(rPanel, 0, wxEXPAND | wxBOTTOM, 0);

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(left_sizer, 1, wxALL, 0);
    button_sizer->Add(Spacer, 0, wxALL, 0);
    button_sizer->Add(right_sizer, 1, wxALL, 0);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(cPanel, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(button_sizer, 0, wxEXPAND | wxBOTTOM, 10);
    main_sizer->Add(dPanel, 0, wxEXPAND | wxBOTTOM, 20);
    main_sizer->Add(switch_Button, 1, wxEXPAND | wxBOTTOM, 10);

    SetSizer(main_sizer);

    Bind(c_LOAD_IMAGE_EVENT, &CaptureButtonPanel::OnLoadImage, this);
}

void CaptureButtonPanel::DisableAllButtons() {
    // Capture_Button->Disable();
    // Load_Button->Disable();
    // ToggleCamera_Button->Disable();
}

void CaptureButtonPanel::EnableAllButtons() {
    // Capture_Button->Enable();
    // Load_Button->Enable();
    // ToggleCamera_Button->Enable();
}

void CaptureButtonPanel::OnLoadImage(wxCommandEvent &e) {

    if (e.GetId() == LOAD_START) {
        DisableAllButtons();
    }

    if (e.GetId() == LOAD_END_CAMERA || e.GetId() == LOAD_END_FILE) {
        EnableAllButtons();
    }
    e.Skip();
}

// clang-format off
BEGIN_EVENT_TABLE(CaptureButtonPanel, wxPanel)
END_EVENT_TABLE()

