#include <UI/CameraPanel/ButtonPanel.hpp>

CameraPanelButton::CameraPanelButton(wxWindow *parent, wxWindowID id,
                                     cv::VideoCapture *camera,
                                     std::vector<ImageData> *imgData,
                                     ThreadPool *pool)
    : wxPanel(parent, id) {

    Capture_Button =
        new ButtonCapture(this, Enum::CP_Capture_Button_ID, camera);
    Load_Button = new ButtonLoad(this, Enum::CP_Load_Button_ID, imgData, pool);
    ToggleCamera_Button =
        new wxButton(this, Enum::CP_Camera_Button_ID, "Toggle Camera");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Capture_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(ToggleCamera_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Load_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);
}

void CameraPanelButton::onCaptureToggle(bool isCapturing) {
    if (isCapturing) {
        Capture_Button->Disable();
        Load_Button->Disable();
    } else {
        Capture_Button->Enable();
        Load_Button->Enable();
    }
}

void CameraPanelButton::DisableAllButtons() {
    Capture_Button->Disable();
    Load_Button->Disable();
}

void CameraPanelButton::EnableAllButtons() {
    Capture_Button->Enable();
    Load_Button->Enable();
}

// clang-format off
BEGIN_EVENT_TABLE(CameraPanelButton, wxPanel)
END_EVENT_TABLE()

