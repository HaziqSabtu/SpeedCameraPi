#ifndef BUTTON_BBOX_HPP
#define BUTTON_BBOX_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonBBox : public ButtonWState {
  public:
    ButtonBBox(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif