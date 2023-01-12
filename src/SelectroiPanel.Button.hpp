#ifndef SELECT_ROI_PANEL_BUTTON
#define SELECT_ROI_PANEL_BUTTON

#include "SelectroiPanel.Image.hpp"
#include <wx/wx.h>

enum {
    Next_Button_ID = 1,
    Prev_Button_ID,
    Sel_Button_ID,
    RemoveROI_Button_ID,
};

class SelectRoiPanelButton : public wxPanel {
  public:
    SelectRoiPanelButton(wxWindow *parent, wxWindowID id, wxWindowID img_id);
    void OnButton(wxCommandEvent &e);
    void OnKeyPress(wxKeyEvent &e);

  private:
    wxWindowID IMG_PANEL_ID;

    int count = 0;
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxButton *Sel_Button;
    wxButton *RemoveROI_Button;

    DECLARE_EVENT_TABLE()
};
#endif
