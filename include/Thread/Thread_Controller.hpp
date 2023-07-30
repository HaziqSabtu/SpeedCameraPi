#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_CalibPreview.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ColorCalib.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "Thread/Thread_Replay.hpp"
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

    virtual void
    startReplayHandler(wxEvtHandler *parent,
                       std::shared_ptr<std::vector<ImageData>> imgData,
                       PanelID panelID);
    void endReplayHandler();

    virtual void startCalibrationHandler(wxEvtHandler *parent,
                                         std::unique_ptr<CameraBase> &camera,
                                         HSVFilter &hsvFilter, BFS &bfs,
                                         RansacLine &ransac, PanelID panelID);
    void endCalibrationHandler();

    virtual void startCalibPreviewHandler(wxEvtHandler *parent,
                                          std::unique_ptr<CameraBase> &camera,
                                          DataPtr data, PanelID panelID);

    void endCalibPreviewHandler();

    virtual void
    startManualCalibrationHandler(wxEvtHandler *parent,
                                  std::unique_ptr<CameraBase> &camera,
                                  PanelID panelID);

    void endManualCalibrationHandler();

    virtual void startColorCalibrationHandler(
        wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
        HSVFilter &hsvFilter, BFS &bfs, PanelID panelID);

    void endColorCalibrationHandler();

    bool isThreadNullptr(ThreadID threadID);

    bool isThreadOwner(ThreadID threadID, PanelID panelID);

    bool isThreadsWithCameraNullptr();

    CaptureThread *getCaptureThread();

    LoadCaptureThread *getLoadCaptureThread();

    LoadFileThread *getLoadFileThread();

    ReplayThread *getReplayThread();

    CalibrationThread *getCalibrationThread();

    CalibPreviewThread *getCalibPreviewThread();

    ManualCalibrationThread *getManualCalibrationThread();

    ColorCalibrationThread *getColorCalibrationThread();

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

    ReplayThread *replayThread;

    CalibrationThread *calibrationThread;

    CalibPreviewThread *calibPreviewThread;

    ManualCalibrationThread *manualCalibrationThread;

    ColorCalibrationThread *colorCalibrationThread;
};