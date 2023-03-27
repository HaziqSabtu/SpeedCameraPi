#ifndef BUTTON_SELECTEDLINE_HPP
#define BUTTON_SELECTEDLINE_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonSelL : public ButtonWState {
  public:
    ButtonSelL(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif