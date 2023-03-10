#ifndef BUTTON_PANEL_HOUGH_HPP
#define BUTTON_PANEL_HOUGH_HPP

#include <UI/Button/Button_Canny.hpp>
#include <UI/Button/Button_Hough.hpp>
#include <Utils/Enum.hpp>
#include <unordered_map>
#include <wx/wx.h>

class ButtonPanelHough : public wxPanel {
  public:
    ButtonPanelHough(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;
    wxBoxSizer *nextprev_sizer;

    ButtonCanny *Canny_Button;
    ButtonHough *Hough_Button;
    wxButton *ClearLine_Button;
    wxButton *Reset_Button;
    wxButton *Next_Button;
    wxButton *Prev_Button;
    wxStaticText *Spacer;

    void OnButton(wxCommandEvent &e);
    DECLARE_EVENT_TABLE();
};
#endif
