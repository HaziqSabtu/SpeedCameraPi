#ifndef CAPTURE_VIEW_BUTTON_HPP
#define CAPTURE_VIEW_BUTTON_HPP

#include <Utils/Enum.hpp>
#include <wx/wx.h>

class CaptureViewPanelButton : public wxPanel {
  public:
    CaptureViewPanelButton(wxWindow *parent, wxWindowID id);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxButton *Next_Button;
    wxButton *Prev_Button;
    DECLARE_EVENT_TABLE();
};
#endif
