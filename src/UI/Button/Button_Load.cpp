#include <UI/Button/Button_Load.hpp>

ButtonLoad::ButtonLoad(wxWindow* parent, wxWindowID id)
    : ButtonWState(parent, id, "Load", "Loading", "Load", false) {
    Bind(wxEVT_BUTTON, &ButtonLoad::OnButton, this);
    Bind(c_CAPTURE_IMAGE_EVENT, &ButtonLoad::OnCaptureEvent, this);
}

ButtonLoad::~ButtonLoad() {}

void ButtonLoad::OnButton(wxCommandEvent& e) {
    toggleState();
    e.Skip();
}

void ButtonLoad::OnCaptureEvent(wxCommandEvent& e) {
    if (e.GetId() == CAPTURE_START) {
        state = true;
    }

    if (e.GetId() == CAPTURE_END) {
        state = false;
    }

    render();
    e.Skip();
}

void ButtonLoad::render() {
    // state ? Enable() : Disable();
    ButtonWState::render();
}