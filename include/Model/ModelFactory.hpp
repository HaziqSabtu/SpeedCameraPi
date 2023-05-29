#pragma once

#include <Model/CaptureModel.hpp>
#include <Model/SharedModel.hpp>
#include <memory>

class ModelFactory {
  public:
    ModelFactory(wxWindow *parent);
    ~ModelFactory();

    std::unique_ptr<CaptureModel> createCaptureModel();

  private:
    std::shared_ptr<SharedModel> sharedModel;
};