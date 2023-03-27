#ifndef BUTTON_LOAD_HPP
#define BUTTON_LOAD_HPP

#include <Event/Event_CaptureImage.hpp>
#include <UI/Button/Button_wState.hpp>

class ButtonLoad : public ButtonWState {
  public:
    ButtonLoad(wxWindow *parent, wxWindowID id);
    ~ButtonLoad();

  private:
    void OnButton(wxCommandEvent &e) override;
    void OnCaptureImage(CaptureImageEvent &e);

    void render() override;
};

#endif