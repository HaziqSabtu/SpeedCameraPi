#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Process.hpp"
#include <Model/ModelEnum.hpp>

#include <Event/Event_ChangePanel.hpp>
#include <Event/Event_Error.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Capture.hpp>
#include <Thread/Thread_LoadCapture.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <Thread/Thread_Process.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Camera/libcam.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>

#include <wx/gdicmn.h>
#include <wx/wx.h>

class Model {
  public:
    Model(wxWindow *parent, wxWindowID id);
    ~Model();
    // TODO: Unified endpoint?
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id);
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                  std::string path);
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id,
                  PanelID panelID);
    void endPoint(wxEvtHandler *parent, PanelID panelID, wxRect rect);

  private:
    SessionData sessionData;
    std::shared_ptr<CameraBase> camera;
    std::shared_ptr<ThreadPool> threadPool;

    CaptureThread *captureThread;
    LoadFileThread *loadFileThread;
    LoadCaptureThread *loadCaptureThread;
    ProcessThread *processThread;

    void initThreads();
    void deleteThreads();

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startLoadFileHandler(wxEvtHandler *parent, std::string path);
    void endLoadFileHandler(wxEvtHandler *parent);

    void startLoadCaptureHandler(wxEvtHandler *parent);
    void endLoadCaptureHandler(wxEvtHandler *parent);

    void startProcessHandler(wxEvtHandler *parent);

    // ChangePanelHandler
    void requestChangePanel(wxEvtHandler *parent, PanelID panelID);

    void changeCapturePanel(wxEvtHandler *parent);

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);
};