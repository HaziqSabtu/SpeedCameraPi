#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/TrimDataPanel/PanelSetEnd.hpp"
#include "UI/Panel/TrimDataPanel/PanelSetStart.hpp"
#include "UI/Panel/TrimDataPanel/PanelStatusTrim.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class TrimDataPanelButton : public BaseButtonPanel {
  public:
    TrimDataPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    TrimButtonMain *MainPanel;
    TrimButtonSetStart *SetStartPanel;
    TrimButtonSetEnd *SetEndPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};