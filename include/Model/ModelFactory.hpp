#pragma once

#include "Model/CalibrationModel.hpp"
#include "Model/RoiModel.hpp"
#include <Model/CaptureModel.hpp>
#include <Model/SharedModel.hpp>
#include <memory>

class ModelFactory {
  public:
    ModelFactory(wxWindow *parent);
    ~ModelFactory();

    std::shared_ptr<SharedModel> getSharedModel();

    std::unique_ptr<CaptureModel> createCaptureModel();
    std::unique_ptr<RoiModel> createRoiModel();
    std::unique_ptr<CalibrationModel> createCalibrationModel();

  private:
    std::shared_ptr<SharedModel> sharedModel;
};