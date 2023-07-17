#include <UI/Button/Button_ToggleCamera.hpp>

ButtonToggleCam::ButtonToggleCam(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Capture", "Camera On", "Camera Off", false) {
    Bind(wxEVT_BUTTON, &ButtonToggleCam::OnButton, this);
    Bind(c_CAPTURE_EVENT, &ButtonToggleCam::OnCapture, this);
}

ButtonToggleCam::~ButtonToggleCam() {}

void ButtonToggleCam::OnButton(wxCommandEvent &e) {
    // toggleState();
    e.Skip();
}

void ButtonToggleCam::OnCapture(wxCommandEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        state = true;
        render();
    }

    if (e.GetId() == CAPTURE_END) {
        state = false;
        render();
    }
}