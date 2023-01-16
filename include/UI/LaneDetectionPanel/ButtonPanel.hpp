#ifndef LANE_DETECTION_PANEL_BUTTON
#define LANE_DETECTION_PANEL_BUTTON

#include <UI/LaneDetectionPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class LaneDetectionPanelButton : public wxPanel {
  public:
    LaneDetectionPanelButton(wxWindow *parent, wxWindowID id);

  private:
    void OnRunAlgorithm(wxCommandEvent &e);
    void OnNext(wxCommandEvent &e);
    void OnPrev(wxCommandEvent &e);

    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Run_Button;

    DECLARE_EVENT_TABLE()
};
#endif
