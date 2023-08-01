#pragma once

#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Button/Button_wState.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/RoiPanel/PanelRoiTools.hpp"
#include "UI/Panel/RoiPanel/PanelStatusRoi.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class RoiPanelButton : public wxPanel {
  public:
    RoiPanelButton(wxWindow *parent, wxWindowID id);

    RoiMainStatusPanel *main_status_panel;

    RoiToolsPanel *roi_tools_panel;

    OKCancelPanel *ok_cancel_panel;

  private:
    wxPanel *button_panel;
    wxStaticText *Spacer;

    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
