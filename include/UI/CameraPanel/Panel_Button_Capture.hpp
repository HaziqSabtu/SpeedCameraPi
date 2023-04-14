#ifndef PANEL_BUTTON_CAPTURE_HPP
#define PANEL_BUTTON_CAPTURE_HPP

#include <UI/Button/Button_Capture.hpp>
#include <UI/Button/Button_Load.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class CameraPanelButton : public wxPanel {
  public:
    CameraPanelButton(wxWindow* parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    ButtonWState* Capture_Button;
    ButtonWState* Load_Button;
    wxButton* ToggleCamera_Button;

  private:
    wxPanel* button_panel;
    wxBoxSizer* button_sizer;

    wxStaticText* Spacer;

    void OnCaptureEvent(wxCommandEvent& e);

    DECLARE_EVENT_TABLE();
};
#endif
