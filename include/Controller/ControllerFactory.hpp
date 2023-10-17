#pragma once

#include "Controller/CaptureController.hpp"
#include "Controller/ColorCalibrationController.hpp"
#include "Controller/DistanceCalibrationController.hpp"
#include "Controller/LaneCalibrationController.hpp"
#include "Controller/LaneManualCalibrationController.hpp"
#include "Controller/ResultController.hpp"
#include "Controller/RoiController.hpp"
#include "Controller/TrimDataController.hpp"
#include <Model/SharedModel.hpp>
#include <memory>

#define CtrlFactoryPtr std::shared_ptr<ControllerFactory>

class ControllerFactory {
  public:
    ControllerFactory(wxWindow *parent);
    ~ControllerFactory();

    ModelPtr getSharedModel();

    CPCPtr createCaptureController();
    LCCPtr createLaneCalibrationController();
    LMCPtr createLaneManualCalibrationController();
    DCCPtr createDistanceCalibrationController();
    CCCPtr createColorCalibrationController();
    ROCPtr createRoiController();
    RSCPtr createResultController();
    TDCPtr createTrimDataController();

  private:
    ModelPtr sharedModel;
};