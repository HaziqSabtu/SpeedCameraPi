#pragma once

#include "Controller/LaneManualCalibrationController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelLeftStatus.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/PanelRightStatus.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Common/Panel_Image.hpp>
#include <UI/Panel/LaneManualCalibrationPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class LaneManualCalibrationPanel : public BasePanelWithTouch {
  public:
    LaneManualCalibrationPanel(wxWindow *parent, wxWindowID id,
                               LMCPtr controller);
    ~LaneManualCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_LANE_MANUAL_CALIBRATION;

    LMCPtr controller;

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnPreviewCamera(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};