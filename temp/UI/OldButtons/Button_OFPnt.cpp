#include <UI/Button/Button_OFPnt.hpp>

ButtonOFPnt::ButtonOFPnt(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "OFPoints", false) {
    Bind(wxEVT_BUTTON, &ButtonOFPnt::OnButton, this);
}

void ButtonOFPnt::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}