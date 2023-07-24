#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include <unordered_map>

class ThreadController {
  public:
    ThreadController();
    ~ThreadController();

    virtual void startCaptureHandler(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera,
                                     PanelID panelID);

    void endCaptureHandler();

    virtual void
    startLoadCaptureHandler(wxEvtHandler *parent,
                            std::unique_ptr<CameraBase> &camera,
                            std::shared_ptr<std::vector<ImageData>> imgData,
                            const int maxFrame, PanelID panelID);

    void endLoadCaptureHandler();

    virtual void startLoadFileHandler(wxEvtHandler *parent, int maxFrame,
                                      std::string path, PanelID panelID);

    void endLoadFileHandler();

    bool isThreadNullptr(ThreadID threadID);

    bool isThreadOwner(ThreadID threadID, PanelID panelID);

    bool isThreadsWithCameraNullptr();

    CaptureThread *getCaptureThread();

    LoadCaptureThread *getLoadCaptureThread();

    LoadFileThread *getLoadFileThread();

    void killAllThreads();

  protected:
    void initThread();
    void deleteThread();

  private:
    std::unordered_map<ThreadID, PanelID> owner;

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);

    CaptureThread *captureThread;

    LoadCaptureThread *loadCaptureThread;

    LoadFileThread *loadFileThread;
};