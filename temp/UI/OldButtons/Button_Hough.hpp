#ifndef BUTTON_HOUGH_HPP
#define BUTTON_HOUGH_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonHough : public ButtonWState {
  public:
    ButtonHough(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif