#include <UI/CameraPanel/ButtonPanel.hpp>

CameraPanelButton::CameraPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    Capture_Button = new wxButton(this, Enum::CP_Capture_Button_ID, "Capture");
    Stop_Button = new wxButton(this, Enum::CP_Stop_Button_ID, "Stop");
    Load_Button = new wxButton(this, Enum::CP_Load_Button_ID, "Load");
    wxStaticText *spacer = new wxStaticText(
        this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Capture_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Stop_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Load_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);

    Stop_Button->Disable();
}

void CameraPanelButton::onCaptureToggle(bool isCapturing) {
    if (isCapturing) {
        Capture_Button->Disable();
        Stop_Button->Enable();
    } else {
        Capture_Button->Enable();
        Stop_Button->Disable();
    }
}

// clang-format off
BEGIN_EVENT_TABLE(CameraPanelButton, wxPanel)
END_EVENT_TABLE()

