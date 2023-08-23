#pragma once

#include "UI/Button/TextButton/TextButton.hpp"
#include "UI/Panel/CapturePanel/PanelStatusCalib.hpp"
#include "UI/Panel/CapturePanel/PanelStatusCapture.hpp"
#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include "UI/Panel/CapturePanel/PanelStatusTools.hpp"
#include <UI/Button/TextButton/Button_Measure.hpp>

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonPanel : public wxPanel {
  public:
    CaptureButtonPanel(wxWindow *parent, wxWindowID id);

    CaptureStatusPanel *cPanel;

    CalibrationStatusPanel *csPanel;

    ROIStatusPanel *rPanel;

    CaptureToolsPanel *tPanel;

    TextButton *switch_Button;

  private:
    wxPanel *button_panel;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *lrSizer;
    wxBoxSizer *main_sizer;

    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE();
};
