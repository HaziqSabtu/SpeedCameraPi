#ifndef PANEL_BUTTON_CAPTURE_HPP
#define PANEL_BUTTON_CAPTURE_HPP

#include <Utils/Enum.hpp>
#include <wx/gtk/button.h>
#include <wx/wx.h>

class CameraPanelButton : public wxPanel {
  public:
    CameraPanelButton(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    ButtonWState *Capture_Button;
    ButtonWState *Load_Button;
    ButtonWState *ToggleCamera_Button;
    wxButton *switchButton;

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxStaticText *Spacer;

    void OnLoadImage(wxCommandEvent &e);

    DECLARE_EVENT_TABLE();
};
#endif
