#pragma once

#include "Controller/CalibrationController.hpp"
#include "Controller/CaptureController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Model/RoiModel.hpp"
#include <Model/SharedModel.hpp>
#include <memory>

class ControllerFactory {
  public:
    ControllerFactory(wxWindow *parent);
    ~ControllerFactory();

    ModelPtr getSharedModel();

    std::unique_ptr<RoiModel> createRoiModel();
    CPCPtr createCaptureModel();
    CLCPtr createCalibrationModel();
    MCCPtr createManualCalibrationController();
    CCCPtr createColorCalibrationController();

  private:
    ModelPtr sharedModel;
};