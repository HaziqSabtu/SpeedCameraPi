#ifndef CAMERA_PANEL_BUTTON_HPP
#define CAMERA_PANEL_BUTTON_HPP

#include <UI/Button/Button_Capture.hpp>
#include <UI/Button/Button_Load.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

enum Button_Type { CAPTURE_BUTTON, LOAD_BUTTON, TOGGLE_CAMERA_BUTTON };
class CameraPanelButton : public wxPanel {
  public:
    CameraPanelButton(wxWindow *parent, wxWindowID id);
    void onCaptureToggle(bool isCapturing);
    void DisableAllButtons();
    void EnableAllButtons();
    wxButton *GetButton(Button_Type type);
    bool GetButtonState(Button_Type type);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    ButtonCapture *Capture_Button;
    ButtonLoad *Load_Button;
    wxButton *ToggleCamera_Button;
    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE();
};
#endif
