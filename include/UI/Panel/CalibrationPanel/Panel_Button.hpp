#pragma once

#include "UI/Panel/CalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusPreview.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusTool.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationPanelButton : public wxPanel {
  public:
    CalibrationPanelButton(wxWindow *parent, wxWindowID id);

    CalibrationMainStatusPanel *cPanel;
    CalibrationToolPanel *ctPanel;
    CalibrationPreviewPanel *cpPanel;
    CalibrationOtherPanel *coPanel;
    OKCancelPanel *okCancelPanel;

  private:
    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE();
};
