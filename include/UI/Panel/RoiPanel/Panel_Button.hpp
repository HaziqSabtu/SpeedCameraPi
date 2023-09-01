#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/RoiPanel/PanelRoiTools.hpp"
#include "UI/Panel/RoiPanel/PanelStatusMain.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class RoiPanelButton : public BaseButtonPanel {
  public:
    RoiPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    RoiButtonMain *MainPanel;

    RoiButtonTools *ToolsPanel;

    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
