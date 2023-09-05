#ifndef BUTTON_TOGGLECAMERA_HPP
#define BUTTON_TOGGLECAMERA_HPP

#include <Event/Event_Preview.hpp>

#include <UI/Button/Button_wState.hpp>

class ButtonToggleCam : public ButtonWState {
  public:
    ButtonToggleCam(wxWindow *parent, wxWindowID id);
    ~ButtonToggleCam();

    void renderOffCamera();

  private:
    void OnButton(wxCommandEvent &e) override;

    void OnCapture(wxCommandEvent &e);
};

#endif