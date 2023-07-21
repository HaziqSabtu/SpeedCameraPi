#pragma once

#include "UI/Panel/CapturePanel/PanelStatusCalib.hpp"
#include "UI/Panel/CapturePanel/PanelStatusCapture.hpp"
#include "UI/Panel/CapturePanel/PanelStatusDebug.hpp"
#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include <UI/Button/Button_Capture.hpp>
#include <UI/Button/Button_Load.hpp>
#include <UI/Button/Button_ToggleCamera.hpp>

#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CaptureButtonPanel : public wxPanel {
  public:
    CaptureButtonPanel(wxWindow *parent, wxWindowID id);
    void DisableAllButtons();
    void EnableAllButtons();

    // ButtonWState *Capture_Button;
    // ButtonWState *Load_Button;
    // ButtonWState *ToggleCamera_Button;
    wxButton *switch_Button;
    // wxButton *calibrate_Button;

    CaptureStatusPanel *cPanel;

    CalibrationStatusPanel *csPanel;

    DebugStatusPanel *dPanel;

    ROIStatusPanel *rPanel;

  private:
    wxPanel *button_panel;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *button_sizer;
    wxBoxSizer *main_sizer;

    wxStaticText *Spacer;

    void OnLoadImage(wxCommandEvent &e);

    DECLARE_EVENT_TABLE();
};
