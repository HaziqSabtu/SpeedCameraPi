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

  private:
    const PanelID panelID = PanelID::PANEL_CAPTURE;
    const PanelID nextPanelID = PanelID::PANEL_ROI;

    std::shared_ptr<SharedModel> shared;

    wxThread *captureThread;
    wxThread *loadFileThread;
    wxThread *loadCaptureThread;

    void initThreads();
    void deleteThreads();

    void startCaptureHandler(wxEvtHandler *parent);

    virtual wxThread *initCaptureThread(wxEvtHandler *parent,
                                        std::shared_ptr<CameraBase> camera);
    void endCaptureHandler();

    void startLoadFileHandler(wxEvtHandler *parent, std::string path);
    virtual wxThread *initLoadFileThread(wxEvtHandler *parent, int maxFrame,
                                         std::string path);
    void endLoadFileHandler();

    void startLoadCaptureHandler(wxEvtHandler *parent);
    virtual wxThread *initLoadCaptureThread(
        wxEvtHandler *parent, std::shared_ptr<CameraBase> camera,
        std::shared_ptr<std::vector<ImageData>> imgData, const int maxFrame);
    void endLoadCaptureHandler();

    void switchPanelHandler(wxEvtHandler *parent);

    void switchToCalibHandler(wxEvtHandler *parent);
    virtual bool isRequirementFulfilled();

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);
};