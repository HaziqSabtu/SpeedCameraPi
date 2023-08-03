#pragma once

#include "UI/Panel/CapturePanel/PanelStatusCalib.hpp"
#include "UI/Panel/CapturePanel/PanelStatusCapture.hpp"
#include "UI/Panel/CapturePanel/PanelStatusDebug.hpp"
#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonPanel : public wxPanel {
  public:
    CaptureButtonPanel(wxWindow *parent, wxWindowID id);

    wxButton *switch_Button;

    CaptureStatusPanel *cPanel;

    CalibrationStatusPanel *csPanel;

    DebugStatusPanel *dPanel;

    ROIStatusPanel *rPanel;

  private:
    wxPanel *button_panel;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *lrSizer;
    wxBoxSizer *main_sizer;

    wxStaticText *Spacer;

    DECLARE_EVENT_TABLE();
};
