#include <UI/Button/Button_BBox.hpp>

ButtonBBox::ButtonBBox(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "BBox", true) {
    Bind(wxEVT_BUTTON, &ButtonBBox::OnButton, this);
}

void ButtonBBox::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}