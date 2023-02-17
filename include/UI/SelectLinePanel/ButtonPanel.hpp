#ifndef SELECT_LINE_PANEL_BUTTON
#define SELECT_LINE_PANEL_BUTTON

#include <Utils/Enum.hpp>
#include <wx/notebook.h>
#include <wx/wx.h>

class SelectLinePanelButton : public wxPanel {
  public:
    SelectLinePanelButton(wxWindow *parent, wxWindowID id);
    void OnCanny();
    void OnHough();

  private:
    bool isCanny = false;
    bool isHough = false;

    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxButton *Canny_Button;
    wxButton *Hough_Button;
    wxButton *Clear_Button;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE()
};
#endif
