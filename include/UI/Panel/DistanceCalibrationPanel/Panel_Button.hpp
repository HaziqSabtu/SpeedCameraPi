#pragma once

#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/DistanceCalibrationPanel/PanelBottomStatus.hpp"
#include "UI/Panel/DistanceCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/DistanceCalibrationPanel/PanelTopStatus.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class DistanceCalibrationPanelButton : public BaseButtonPanel {
  public:
    DistanceCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    DistanceCalibrationButtonMain *MainPanel;
    DistanceCalibrationButtonBottom *BottomPanel;
    DistanceCalibrationButtonTop *TopPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *lrSizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
