#include <UI/Button/Button_SelL.hpp>

ButtonSelL::ButtonSelL(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Line", false) {
    Bind(wxEVT_BUTTON, &ButtonSelL::OnButton, this);
}

void ButtonSelL::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}