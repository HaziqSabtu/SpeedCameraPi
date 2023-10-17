#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/LaneCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/LaneCalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/LaneCalibrationPanel/PanelStatusTool.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneCalibrationPanelButton : public BaseButtonPanel {
  public:
    LaneCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    LaneCalibrationButtonMain *MainPanel;
    LaneCalibrationButtonTool *ToolPanel;
    LaneCalibrationButtonOther *OtherPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE();
};
