#ifndef OPTICAL_FLOW_PANEL_BUTTON
#define OPTICAL_FLOW_PANEL_BUTTON

#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class OpticalFlowPanelButton : public wxPanel {
  public:
    OpticalFlowPanelButton(wxWindow *parent, wxWindowID id);
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);
    void OnToggleTracker(wxCommandEvent &e);
    void OnToggleOpticalFlow(wxCommandEvent &e);
    void OnEval(wxCommandEvent &e);
    void OnNextPage(wxCommandEvent &e);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Track_Button;
    wxButton *RemoveROI_Button;
    wxButton *Optical_Button;
    wxButton *Eval_Button;
    wxButton *NextPage_Button;

    DECLARE_EVENT_TABLE()
};
#endif
