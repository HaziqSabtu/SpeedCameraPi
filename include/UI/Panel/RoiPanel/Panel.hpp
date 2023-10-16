#pragma once

#include "Controller/ManualCalibrationController.hpp"
#include "Controller/RoiController.hpp"
#include "Event/Event_UpdatePreview.hpp"
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
#include <UI/Panel/RoiPanel/Panel_Button.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class RoiPanel : public BasePanelWithTouch {
  public:
    RoiPanel(wxWindow *parent, wxWindowID id, ROCPtr controller);
    ~RoiPanel();

  private:
    const PanelID panel_id = PANEL_ROI;

    ROCPtr controller;

    void ToggleRoiButtonHandler(BitmapButtonT2 *button);
    void TogglePreviewButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnRoi(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};