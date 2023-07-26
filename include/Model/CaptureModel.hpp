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

    void e_UpdateState(wxEvtHandler *parent);

    void e_ClearImageData(wxEvtHandler *parent);

    void e_CameraStart(wxEvtHandler *parent);
    void e_CameraEnd(wxEvtHandler *parent);

    void e_LoadFileStart(wxEvtHandler *parent, std::string path);
    void e_LoadFileEnd(wxEvtHandler *parent);

    void e_LoadCaptureStart(wxEvtHandler *parent);
    void e_LoadCaptureEnd(wxEvtHandler *parent);

    void e_ReplayStart(wxEvtHandler *parent);
    void e_ReplayEnd(wxEvtHandler *parent);

    void e_ChangeToCalibPanel(wxEvtHandler *parent);

  private:
    const PanelID panelID = PanelID::PANEL_CAPTURE;
    std::shared_ptr<SharedModel> shared;

  private:
    void checkPreCondition();

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startLoadFileHandler(wxEvtHandler *parent, std::string path);
    void endLoadFileHandler();

    void startLoadCaptureHandler(wxEvtHandler *parent);
    void endLoadCaptureHandler();

    void switchPanelHandler(wxEvtHandler *parent);
};