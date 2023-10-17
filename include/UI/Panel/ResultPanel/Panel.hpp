#pragma once

#include "Controller/LaneManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Controller/RoiController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateSpeed.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Button/BitmapButton/Type2/BitmapButtonT2.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/Common/Panel_Image.hpp>
#include <UI/Panel/ResultPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class ResultPanel : public BasePanel {
  public:
    ResultPanel(wxWindow *parent, wxWindowID id, RSCPtr controller);
    ~ResultPanel();

  private:
    const PanelID panel_id = PANEL_RESULT;

    RSCPtr controller;

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void ToggleBoxButtonHandler(BitmapButtonT2 *button);
    void ToggleLinesButtonHandler(BitmapButtonT2 *button);
    void ToggleLanesButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnProcessImage(wxCommandEvent &e);
    void OnCapturePreview(wxCommandEvent &e);
    void OnUpdateSpeed(UpdateSpeedEvent &e);

    DECLARE_EVENT_TABLE()
};