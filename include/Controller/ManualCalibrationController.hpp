#pragma once

#include "Model/SessionData.hpp"
#include <Model/SharedModel.hpp>

#define MCCPtr std::unique_ptr<ManualCalibrationController>

class ManualCalibrationController {
  public:
    ManualCalibrationController(ModelPtr sharedModel);
    ~ManualCalibrationController();

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ChangeToCalibrationPanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_MANUAL_CALIBRATION;
    ModelPtr shared;

  private:
    void checkPreCondition();
};