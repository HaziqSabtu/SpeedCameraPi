#pragma once

#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Button/Button_wState.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/wx.h>

class CalibrationPanelButton : public wxPanel {
  public:
    CalibrationPanelButton(wxWindow *parent, wxWindowID id);
    wxButton *switch_Button;
    ButtonWState *start_Button;

  private:
    wxPanel *button_panel;
    wxBoxSizer *button_sizer;

    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE();
};
