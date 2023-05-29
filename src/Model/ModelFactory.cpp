#include <Model/ModelFactory.hpp>
#include <memory>

ModelFactory::ModelFactory(wxWindow *parent) {
    sharedModel = std::make_shared<SharedModel>(parent);
}

ModelFactory::~ModelFactory() { sharedModel = nullptr; }

std::unique_ptr<CaptureModel> ModelFactory::createCaptureModel() {
    return std::make_unique<CaptureModel>(sharedModel);
}