#ifndef BUTTON_OPTICALFLOW_POINTS_HPP
#define BUTTON_OPTICALFLOW_POINTS_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonOFPnt : public ButtonWState {
  public:
    ButtonOFPnt(wxWindow *parent, wxWindowID id);

  private:
    void OnButton(wxCommandEvent &e) override;
};

#endif