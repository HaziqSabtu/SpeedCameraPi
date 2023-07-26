#pragma once

#include "Model/SessionData.hpp"
#include <Model/SharedModel.hpp>

#define CCCPtr std::unique_ptr<ColorCalibrationController>

class ColorCalibrationController {
  public:
    ColorCalibrationController(ModelPtr sharedModel);
    ~ColorCalibrationController();

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ChangeToCalibrationPanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_COLOR_CALIBRATION;
    ModelPtr shared;

  private:
    void checkPreCondition();
};