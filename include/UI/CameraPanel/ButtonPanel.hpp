#ifndef CAMERA_PANEL_BUTTON_HPP
#define CAMERA_PANEL_BUTTON_HPP

#include <Utils/Enum.hpp>
#include <wx/wx.h>

class CameraPanelButton : public wxPanel {
  public:
    CameraPanelButton(wxWindow *parent, wxWindowID id);
    void onCaptureToggle(bool isCapturing);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxButton *Capture_Button;
    wxButton *Stop_Button;
    DECLARE_EVENT_TABLE();
};
#endif
