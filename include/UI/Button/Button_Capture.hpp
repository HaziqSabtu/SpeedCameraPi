#ifndef BUTTON_CAPTURE_HPP
#define BUTTON_CAPTURE_HPP

#include <UI/Button/Button_wState.hpp>

class ButtonCapture : public ButtonWState {
  public:
    ButtonCapture(wxWindow *parent, wxWindowID id);
    ~ButtonCapture();

  private:
    void OnButton(wxCommandEvent &e) override;

    void startCapture();
    void stopCapture();
    void clearPointer();

    void render() override;
};

#endif