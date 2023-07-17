#pragma once

#include <UI/Button/Button_Capture.hpp>
#include <UI/Button/Button_Load.hpp>
#include <UI/Button/Button_ToggleCamera.hpp>

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/wx.h>

class CaptureButtonPanel : public wxPanel {
  public:
    CaptureButtonPanel(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    ButtonWState *Capture_Button;
    ButtonWState *Load_Button;
    ButtonWState *ToggleCamera_Button;
    wxButton *switch_Button;
    wxButton *calibrate_Button;

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxStaticText *Spacer;

    void OnLoadImage(wxCommandEvent &e);

    DECLARE_EVENT_TABLE();
};
