#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/HorizontalCalibrationPanel/PanelBottomStatus.hpp"
#include "UI/Panel/HorizontalCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/HorizontalCalibrationPanel/PanelStatusPreview.hpp"
#include "UI/Panel/HorizontalCalibrationPanel/PanelTopStatus.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class HorizontalCalibrationPanelButton : public BaseButtonPanel {
  public:
    HorizontalCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    HorizontalCalibrationButtonMain *MainPanel;
    HorizontalCalibrationButtonBottom *BottomPanel;
    HorizontalCalibrationButtonTop *TopPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
