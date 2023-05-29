#pragma once

#include "Model/SessionData.hpp"
#include <Model/SharedModel.hpp>

class CaptureModel {
  public:
    CaptureModel(std::shared_ptr<SharedModel> sharedModel);
    ~CaptureModel();

    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                  std::string path);
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id);

  private:
    const PanelID panelID = PanelID::PANEL_CAPTURE;

    std::shared_ptr<SharedModel> shared;

    CaptureThread *captureThread;
    LoadFileThread *loadFileThread;
    LoadCaptureThread *loadCaptureThread;

    void initThreads();
    void deleteThreads();

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startLoadFileHandler(wxEvtHandler *parent, std::string path);
    void endLoadFileHandler();

    void startLoadCaptureHandler(wxEvtHandler *parent);
    void endLoadCaptureHandler();

    void switchPanelHandler(wxEvtHandler *parent);
    bool isRequirementFulfilled();

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);
};