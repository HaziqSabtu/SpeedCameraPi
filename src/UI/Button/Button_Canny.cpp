#include <UI/Button/Button_Canny.hpp>

ButtonCanny::ButtonCanny(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Canny", false) {
    Bind(wxEVT_BUTTON, &ButtonCanny::OnButton, this);
}

void ButtonCanny::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}