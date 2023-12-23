#include <UI/Button/Button_Hough.hpp>

ButtonHough::ButtonHough(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Hough", true) {
    Bind(wxEVT_BUTTON, &ButtonHough::OnButton, this);
}

void ButtonHough::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}