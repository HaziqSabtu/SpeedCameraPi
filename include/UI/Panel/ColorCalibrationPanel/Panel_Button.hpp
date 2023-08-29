#pragma once

#include "Model/AppState.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelBlueStatus.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelStatusOther.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ColorCalibrationPanelButton : public BaseButtonPanel {
  public:
    ColorCalibrationPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    ColorCalibrationMainStatusPanel *main_status_panel;

    BlueStatusPanel *blue_status_panel;
    YellowStatusPanel *yellow_status_panel;

    ColorCalibrationOtherPanel *other_status_panel;

    OKCancelPanel *ok_cancel_panel;

  private:
    wxStaticText *spacer;

    wxBoxSizer *left_sizer;
    wxBoxSizer *right_sizer;
    wxBoxSizer *button_sizer;

    wxBoxSizer *okSizer;

    DECLARE_EVENT_TABLE();
};
