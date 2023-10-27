#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelStatusPreview.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneManualCalibrationPanelButton : public BaseButtonPanel {
  public:
    LaneManualCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    LaneManualCalibrationButtonMain *MainPanel;
    LaneManualCalibrationButtonLeft *LeftPanel;
    LaneManualCalibrationButtonRight *RightPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
