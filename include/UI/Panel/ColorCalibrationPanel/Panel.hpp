#pragma once

#include "Controller/ColorCalibrationController.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelBlueStatus.hpp"
#include "UI/Panel/ColorCalibrationPanel/PanelYellowStatus.hpp"
#include "UI/Panel/Common/BasePanel.hpp"
#include "UI/StaticText/Statustext.hpp"
#include "UI/StaticText/Titletext.hpp"
#include <UI/Panel/ColorCalibrationPanel/Panel_Button.hpp>
#include <UI/Panel/Common/Panel_Image.hpp>

#include <Utils/Config/AppConfig.hpp>
#include <Utils/Enum.hpp>

#include <memory>
#include <unordered_map>
#include <wx/gtk/button.h>
#include <wx/sizer.h>
#include <wx/wx.h>

/**
 * @brief The color calibration panel
 * @image html colorcalibrationpanel.png
 * @image latex colorcalibrationpanel.png
 */
class ColorCalibrationPanel : public BasePanelWithTouch {
  public:
    ColorCalibrationPanel(wxWindow *parent, wxWindowID id, CCCPtr controller);
    ~ColorCalibrationPanel();

  private:
    const PanelID panel_id = PANEL_COLOR_CALIBRATION;

    CCCPtr controller;

    void doPostLeftDown() override;

    void ToggleCameraButtonHandler(BitmapButtonT2 *button);
    void ToggleCalibrationButtonHandler(BitmapButtonT2 *button);

    void OnButton(wxCommandEvent &e);
    void OnCalibrationEvent(wxCommandEvent &e);

    DECLARE_EVENT_TABLE()
};