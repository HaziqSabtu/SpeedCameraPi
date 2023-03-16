#ifndef BUTTON_CAPTURE_HPP
#define BUTTON_CAPTURE_HPP

#include <Event/Event_CaptureImage.hpp>
#include <UI/Button/Button_wState.hpp>

class ButtonCapture : public ButtonWState {
  public:
    ButtonCapture(wxWindow *parent, wxWindowID id);
    ~ButtonCapture();

  private:
    void OnButton(wxCommandEvent &e) override;
    void OnCaptureImage(CaptureImageEvent &e);

    void render() override;
};

#endif