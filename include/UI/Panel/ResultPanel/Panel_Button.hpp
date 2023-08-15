#pragma once

#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/ResultPanel/PanelResultPreview.hpp"
#include "UI/Panel/ResultPanel/PanelStatusResult.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanelButton : public wxPanel {
  public:
    ResultPanelButton(wxWindow *parent, wxWindowID id);

    ResultMainStatusPanel *main_status_panel;
    ResultPreviewStatusPanel *preview_status_panel;

    OKCancelPanel *ok_cancel_panel;

  private:
    wxPanel *button_panel;
    wxStaticText *Spacer;

    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
