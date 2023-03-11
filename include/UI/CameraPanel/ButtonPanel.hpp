#ifndef CAMERA_PANEL_BUTTON_HPP
#define CAMERA_PANEL_BUTTON_HPP

#include <UI/Button/Button_Capture.hpp>
#include <UI/Button/Button_Load.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class CameraPanelButton : public wxPanel {
  public:
    CameraPanelButton(wxWindow *parent, wxWindowID id, cv::VideoCapture *camera,
                      ThreadPool *pool);
    void onCaptureToggle(bool isCapturing);
    void DisableAllButtons();
    void EnableAllButtons();

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
