#include <UI/Button/Button_Capture.hpp>

ButtonCapture::ButtonCapture(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Capture", "Capturing", "Capture", false) {
    Bind(wxEVT_BUTTON, &ButtonCapture::OnButton, this);
    Bind(c_CAPTURE_IMAGE_EVENT, &ButtonCapture::OnCaptureImage, this);
}

ButtonCapture::~ButtonCapture() {}

void ButtonCapture::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}

void ButtonCapture::render() { ButtonWState::render(); }

void ButtonCapture::OnCaptureImage(CaptureImageEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        Disable();
    } else if (e.GetId() == CAPTURE_END) {
        Enable();
        toggleState();
    }
    e.Skip();
}