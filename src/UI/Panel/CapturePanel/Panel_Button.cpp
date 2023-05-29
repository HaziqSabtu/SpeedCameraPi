#include <UI/Panel/CapturePanel/Panel_Button.hpp>

CaptureButtonPanel::CaptureButtonPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    Capture_Button = new ButtonCapture(this, Enum::CP_Capture_Button_ID);
    Load_Button = new ButtonLoad(this, Enum::CP_Load_Button_ID);
    ToggleCamera_Button =
        new ButtonToggleCam(this, Enum::CP_ToggleCamera_Button_ID);
    switch_Button = new wxButton(this, Enum::CP_SWITCH_Button_ID, "Switch");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Capture_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(ToggleCamera_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Load_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(switch_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);

    Bind(c_LOAD_IMAGE_EVENT, &CaptureButtonPanel::OnLoadImage, this);
}

void CaptureButtonPanel::DisableAllButtons() {
    Capture_Button->Disable();
    Load_Button->Disable();
    ToggleCamera_Button->Disable();
}

void CaptureButtonPanel::EnableAllButtons() {
    Capture_Button->Enable();
    Load_Button->Enable();
    ToggleCamera_Button->Enable();
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

