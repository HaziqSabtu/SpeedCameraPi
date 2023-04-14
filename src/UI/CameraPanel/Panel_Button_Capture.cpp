#include <UI/CameraPanel/Panel_Button_Capture.hpp>

CameraPanelButton::CameraPanelButton(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id) {

    Capture_Button = new ButtonCapture(this, Enum::CP_Capture_Button_ID);
    Load_Button = new ButtonLoad(this, Enum::CP_Load_Button_ID);
    ToggleCamera_Button =
      new wxButton(this, Enum::CP_Camera_Button_ID, "Toggle Camera");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Capture_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(ToggleCamera_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Load_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);

    Bind(c_CAPTURE_IMAGE_EVENT, &CameraPanelButton::OnCaptureEvent, this);
}

void CameraPanelButton::DisableAllButtons() {
    Capture_Button->Disable();
    Load_Button->Disable();
    ToggleCamera_Button->Disable();
}

void CameraPanelButton::EnableAllButtons() {
    Capture_Button->Enable();
    Load_Button->Enable();
    ToggleCamera_Button->Enable();
}

void CameraPanelButton::OnCaptureEvent(wxCommandEvent& e) {
    if (e.GetId() == CAPTURE_START) {
        DisableAllButtons();
    }

    if (e.GetId() == CAPTURE_END) {
        EnableAllButtons();
    }
    e.Skip();
}

// clang-format off
BEGIN_EVENT_TABLE(CameraPanelButton, wxPanel)
END_EVENT_TABLE()

