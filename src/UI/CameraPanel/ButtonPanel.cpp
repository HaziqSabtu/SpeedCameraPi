#include <UI/CameraPanel/ButtonPanel.hpp>

CameraPanelButton::CameraPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    Capture_Button = new wxButton(this, Enum::CP_Capture_Button_ID, "Capture");
    Stop_Button = new wxButton(this, Enum::CP_Stop_Button_ID, "Stop");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Capture_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Stop_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);

    // Capture_Button->Disable();
    Stop_Button->Disable();
}

// clang-format off
BEGIN_EVENT_TABLE(CameraPanelButton, wxPanel)
END_EVENT_TABLE()

