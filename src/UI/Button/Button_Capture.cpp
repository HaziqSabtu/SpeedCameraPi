#include <UI/Button/Button_Capture.hpp>

ButtonCapture::ButtonCapture(wxWindow* parent, wxWindowID id)
    : ButtonWState(parent, id, "Capture", "Capturing", "Capture", false) {
    Bind(wxEVT_BUTTON, &ButtonCapture::OnButton, this);
    Bind(c_LOAD_IMAGE_EVENT, &ButtonCapture::OnLoadImage, this);
}

ButtonCapture::~ButtonCapture() {}

void ButtonCapture::OnButton(wxCommandEvent& e) {
    toggleState();
    e.Skip();
}

void ButtonCapture::render() { ButtonWState::render(); }

void ButtonCapture::OnLoadImage(wxCommandEvent& e) {

    if (e.GetId() == LOAD_END_CAMERA) {
        state = false;
    }

    render();
    e.Skip();
    e.Skip();
}