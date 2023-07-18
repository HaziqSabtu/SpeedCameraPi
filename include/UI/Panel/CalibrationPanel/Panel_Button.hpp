#pragma once

#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Button/Button_wState.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/wx.h>

class CalibrationPanelButton : public wxPanel {
  public:
    CalibrationPanelButton(wxWindow *parent, wxWindowID id);
    wxButton *start_Button;
    wxButton *recalibrate_Button;
    wxButton *manual_Button;
    wxButton *cancel_Button;
    wxButton *OK_Button;
    ButtonWState *camera_Button;

  private:
    wxPanel *button_panel;
    wxStaticText *Spacer;
    wxStaticText *left_Spacer;
    wxStaticText *right_Spacer;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
