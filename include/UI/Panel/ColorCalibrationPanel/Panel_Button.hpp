#pragma once

#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ColorCalibrationPanelButton : public wxPanel {
  public:
    ColorCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    ManualCalibrationMainStatusPanel *main_status_panel;

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

    wxBoxSizer *okSizer;

    DECLARE_EVENT_TABLE();
};
