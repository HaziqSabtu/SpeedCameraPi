#ifndef BUTTON_CANNY_HPP
#define BUTTON_CANNY_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonCanny : public ButtonWState {
  public:
    ButtonCanny(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif