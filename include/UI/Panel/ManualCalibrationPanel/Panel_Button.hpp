#pragma once

#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationPanelButton : public wxPanel {
  public:
    ManualCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    ManualCalibrationMainStatusPanel *main_status_panel;

    LeftStatusPanel *left_status_panel;
    RightStatusPanel *right_status_panel;

    OKCancelPanel *ok_cancel_panel;

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
