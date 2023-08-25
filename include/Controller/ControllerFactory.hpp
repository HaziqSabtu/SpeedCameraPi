#pragma once

#include "Controller/CalibrationController.hpp"
#include "Controller/CaptureController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Controller/ManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Controller/RoiController.hpp"
#include "Controller/TrimDataController.hpp"
#include <Model/SharedModel.hpp>
#include <memory>

class ControllerFactory {
  public:
    ControllerFactory(wxWindow *parent);
    ~ControllerFactory();

    ModelPtr getSharedModel();

    CPCPtr createCaptureController();
    CLCPtr createCalibrationController();
    MCCPtr createManualCalibrationController();
    CCCPtr createColorCalibrationController();
    ROCPtr createRoiController();
    RSCPtr createResultController();
    TDCPtr createTrimDataController();

  private:
    ModelPtr sharedModel;
};