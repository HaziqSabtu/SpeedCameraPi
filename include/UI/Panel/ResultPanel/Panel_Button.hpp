#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/TextButton/Type2/TextButtonT2.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/Panel/ManualCalibrationPanel/PanelStatusCalib.hpp"
#include "UI/Panel/ResultPanel/PanelResultPreview.hpp"
#include "UI/Panel/ResultPanel/PanelStatusResult.hpp"
#include <Utils/Enum.hpp>

#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanelButton : public BaseButtonPanel {
  public:
    ResultPanelButton(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    ResultMainStatusPanel *main_status_panel;
    ResultPreviewStatusPanel *preview_status_panel;

    TextButton *back_button;

  private:
    wxStaticText *spacer;

    wxBoxSizer *button_sizer;

    DECLARE_EVENT_TABLE();
};
