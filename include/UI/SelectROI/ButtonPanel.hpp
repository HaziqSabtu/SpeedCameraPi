#ifndef SELECT_ROI_PANEL_BUTTON
#define SELECT_ROI_PANEL_BUTTON

#include <UI/SelectROI/ImagePanel.hpp>
#include <Utils/Enum.hpp>
#include <wx/wx.h>

class SelectRoiPanelButton : public wxPanel {
  public:
    SelectRoiPanelButton(wxWindow *parent, wxWindowID id, wxWindowID img_id);
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
