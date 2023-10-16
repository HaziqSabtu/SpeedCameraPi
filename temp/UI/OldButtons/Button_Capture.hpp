#ifndef BUTTON_CAPTURE_HPP
#define BUTTON_CAPTURE_HPP

#include <Event/Event_LoadImage.hpp>
#include <UI/Button/Button_wState.hpp>

class ButtonCapture : public ButtonWState {
  public:
    ButtonCapture(wxWindow* parent, wxWindowID id);
    ~ButtonCapture();

  private:
    void OnButton(wxCommandEvent& e) override;
    void OnLoadImage(wxCommandEvent& e);

    void render() override;
};

#endif