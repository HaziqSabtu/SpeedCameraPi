#pragma once

#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusPreview.hpp"
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

    ManualCalibrationPreviewPanel *preview_panel;

    OKCancelPanel *ok_cancel_panel;

  private:
    wxStaticText *Spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
