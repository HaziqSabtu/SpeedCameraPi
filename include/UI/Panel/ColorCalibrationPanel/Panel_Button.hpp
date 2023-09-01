#pragma once

#include "Model/AppState.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelBlueStatus.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelStatusMain.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ColorCalibrationPanelButton : public BaseButtonPanel {
  public:
    ColorCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    ColorCalibrationButtonMain *MainPanel;
    ColorCalibrationButtonBlue *BluePanel;
    ColorCalibrationButtonYellow *YellowPanel;
    ColorCalibrationButtonOther *OtherPanel;
    OKCancelPanel *OkCancelPanel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
