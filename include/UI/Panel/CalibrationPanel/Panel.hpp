#pragma once

#include "Controller/CalibrationController.hpp"
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
#include <UI/Panel/CalibrationPanel/Panel_Button.hpp>
#include <UI/Panel/Common/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

class CalibrationPanel : public BasePanelWithTouch {
  public:
    CalibrationPanel(wxWindow *parent, wxWindowID id, CLCPtr controller);
    ~CalibrationPanel();

  private:
    const PanelID panel_id = PANEL_CALIBRATION;

    CLCPtr controller;

    void doPostLeftDown() override;

    void TogglePreviewButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);
    void OnPreviewCapture(wxCommandEvent &e);
    void OnPreviewCamera(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};