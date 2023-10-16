#pragma once

#include "UI/Panel/CalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusPreview.hpp"
#include "UI/Panel/CalibrationPanel/PanelStatusTool.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationPanelButton : public BaseButtonPanel {
  public:
    CalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    CalibrationButtonMain *MainPanel;
    CalibrationButtonTool *ToolPanel;
    // CalibrationButtonPreview *PreviewPanel;
    CalibrationButtonOther *OtherPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxBoxSizer *main_sizer;

    DECLARE_EVENT_TABLE();
};
