#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusPreview.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ManualCalibrationPanelButton : public BaseButtonPanel {
  public:
    ManualCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    ManualCalibrationButtonMain *MainPanel;
    ManualCalibrationButtonLeft *LeftPanel;
    ManualCalibrationButtonRight *RightPanel;
    ManualCalibrationButtonPreview *PreviewPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
