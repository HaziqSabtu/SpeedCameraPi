#ifndef BUTTON_BOTTOM_LINE_HPP
#define BUTTON_BOTTOM_LINE_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonBotL : public ButtonWState {
  public:
    ButtonBotL(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif