#pragma once

#include "UI/Button/TextButton/TextButton.hpp"
#include "UI/Panel/CapturePanel/PanelStatusCalib.hpp"
#include "UI/Panel/CapturePanel/PanelStatusMain.hpp"
#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include "UI/Panel/CapturePanel/PanelStatusTools.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include <UI/Button/TextButton/Button_Measure.hpp>

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonPanel : public BaseButtonPanel {
  public:
    CaptureButtonPanel(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    CaptureButtonMain *MainPanel;

    CaptureButtonCalibration *CalibrationPanel;

    CaptureButtonROI *RoiPanel;

    CaptureButtonTools *ToolsPanel;

    TextButton *Measure_Button;

  private:
    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *lrSizer;
    wxBoxSizer *main_sizer;

    wxStaticText *spacer;

    DECLARE_EVENT_TABLE();
};
