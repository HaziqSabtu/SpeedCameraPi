#include <UI/Button/Button_BotL.hpp>

ButtonBotL::ButtonBotL(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "BotL", false) {
    Bind(wxEVT_BUTTON, &ButtonBotL::OnButton, this);
}

void ButtonBotL::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}