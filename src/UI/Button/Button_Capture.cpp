#include <UI/Button/Button_Capture.hpp>

ButtonCapture::ButtonCapture(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Capture", "Capture", "Capturing", false) {
    Bind(wxEVT_BUTTON, &ButtonCapture::OnButton, this);
}

ButtonCapture::~ButtonCapture() {}

void ButtonCapture::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}

void ButtonCapture::render() { ButtonWState::render(); }