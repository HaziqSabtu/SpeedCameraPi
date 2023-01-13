#ifndef OPTICAL_FLOW_PANEL_BUTTON
#define OPTICAL_FLOW_PANEL_BUTTON

#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class OpticalFlowPanelButton : public wxPanel {
  public:
    OpticalFlowPanelButton(wxWindow *parent, wxWindowID id);
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);
    void OnToggleTracker(wxCommandEvent &e);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Track_Button;
    wxButton *RemoveROI_Button;

    DECLARE_EVENT_TABLE()
};
#endif
