#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Model/SharedModel.hpp>
#include <memory>
#include <wx/event.h>
#include <wx/thread.h>

class CaptureModel {
  public:
    CaptureModel(std::shared_ptr<SharedModel> sharedModel);
    ~CaptureModel();

    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                  std::string path);
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id);

    void e_UpdateState(wxEvtHandler *parent);

  private:
    const PanelID panelID = PanelID::PANEL_CAPTURE;
    const PanelID nextPanelID = PanelID::PANEL_ROI;

    std::shared_ptr<SharedModel> shared;

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startLoadFileHandler(wxEvtHandler *parent, std::string path);
    void endLoadFileHandler();

    void startLoadCaptureHandler(wxEvtHandler *parent);
    void endLoadCaptureHandler();

    void switchPanelHandler(wxEvtHandler *parent);

    void switchToCalibHandler(wxEvtHandler *parent);
    virtual bool isRequirementFulfilled();
};