#ifndef SELECT_ROI_PANEL_BUTTON
#define SELECT_ROI_PANEL_BUTTON

#include <UI/OpticalFlowPanel/ImagePanel.hpp>
#include <UI/SelectROIPanel/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class SelectRoiPanelButton : public wxPanel {
  public:
    SelectRoiPanelButton(wxWindow *parent, wxWindowID id);

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Sel_Button;
    wxButton *RemoveROI_Button;
    wxButton *NextPage_Button;

    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);
    void OnNextPage(wxCommandEvent &e);
    DECLARE_EVENT_TABLE()
};
#endif
