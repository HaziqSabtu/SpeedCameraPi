#ifndef OPTICAL_FLOW_PANEL_BUTTON
#define OPTICAL_FLOW_PANEL_BUTTON

#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class OpticalFlowPanelButton : public wxPanel {
  public:
    OpticalFlowPanelButton(wxWindow *parent, wxWindowID id, wxWindowID img_id);
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);

  private:
    wxWindowID IMG_PANEL_ID;

    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Sel_Button;
    wxButton *RemoveROI_Button;

    DECLARE_EVENT_TABLE()
};
#endif
