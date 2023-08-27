#pragma once

#include "Model/ExtraModel.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_CalibPreview.hpp"
#include "Thread/Thread_CalibPreviewCapture.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_CalibrationCapture.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ColorCalib.hpp"
#include "Thread/Thread_ColorCalibPreview.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "Thread/Thread_ManualCalibCapture.hpp"
#include "Thread/Thread_Process.hpp"
#include "Thread/Thread_Replay.hpp"
#include "Thread/Thread_ResultPreview.hpp"
#include "Thread/Thread_Roi.hpp"
#include "Thread/Thread_RoiPreview.hpp"
#include "Thread/Thread_SaveData.hpp"
#include "Thread/Thread_TrimData.hpp"
#include <unordered_map>

class ThreadController {
  public:
    ThreadController();
    ~ThreadController();

    virtual void startCaptureHandler(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera,
                                     PanelID panelID);
    void endCaptureHandler();

    virtual void startLoadCaptureHandler(wxEvtHandler *parent,
                                         std::unique_ptr<CameraBase> &camera,
                                         DataPtr data, const int maxFrame,
                                         const bool Debug_ShowImage,
                                         const bool Debug_Save,
                                         PanelID panelID);
    void endLoadCaptureHandler();

    virtual void startLoadFileHandler(wxEvtHandler *parent, DataPtr data,
                                      int maxFrame, std::string path,
                                      PanelID panelID);
    void endLoadFileHandler();

    virtual void startSaveFileHandler(wxEvtHandler *parent, DataPtr data,
                                      PanelID panelID);

    void endSaveFileHandler();

    virtual void startReplayHandler(wxEvtHandler *parent, DataPtr data,
                                    PanelID panelID);
    void endReplayHandler();

    virtual void startCalibrationHandler(wxEvtHandler *parent,
                                         std::unique_ptr<CameraBase> &camera,
                                         PanelID panelID);
    void endCalibrationHandler();

    virtual void startCaptureCalibrationHandler(wxEvtHandler *parent,
                                                DataPtr data, PanelID panelID);

    void endCaptureCalibrationHandler();

    virtual void startCalibPreviewHandler(wxEvtHandler *parent,
                                          std::unique_ptr<CameraBase> &camera,
                                          DataPtr data, PanelID panelID);

    void endCalibPreviewHandler();

    virtual void startCalibCapturePreviewHandler(wxEvtHandler *parent,
                                                 DataPtr data, PanelID panelID);

    void endCalibCapturePreviewHandler();

    virtual void
    startManualCalibrationHandler(wxEvtHandler *parent,
                                  std::unique_ptr<CameraBase> &camera,
                                  PanelID panelID);

    void endManualCalibrationHandler();

    virtual void startManualCalibrationCaptureHandler(wxEvtHandler *parent,
                                                      DataPtr data,
                                                      PanelID panelID);

    void endManualCalibrationCaptureHandler();

    virtual void
    startColorCalibrationHandler(wxEvtHandler *parent,
                                 std::unique_ptr<CameraBase> &camera,
                                 PanelID panelID);
    void endColorCalibrationHandler();

    virtual void
    startColorCalibPreviewHandler(wxEvtHandler *parent,
                                  std::unique_ptr<CameraBase> &camera,
                                  CCModelPtr ccExtraModel, PanelID panelID);

    void endColorCalibPreviewHandler();

    virtual void startRoiHandler(wxEvtHandler *parent, DataPtr data,
                                 PanelID panelID);

    void endRoiHandler();

    virtual void startRoiPreviewHandler(wxEvtHandler *parent, DataPtr data,
                                        PanelID panelID);

    void endRoiPreviewHandler();

    virtual void startProcessHandler(wxEvtHandler *parent, POOLPtr threadPool,
                                     DataPtr data, PanelID panelID);

    void endProcessHandler();

    virtual void startResultPreviewHandler(wxEvtHandler *parent, DataPtr data,
                                           PanelID panelID);

    void endResultPreviewHandler();

    virtual void startTrimDataHandler(wxEvtHandler *parent, DataPtr data,
                                      PanelID panelID);

    void endTrimDataHandler();

    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    bool isThreadNullptr(ThreadID threadID);

    bool isThreadRunning(ThreadID threadID);

    bool isThreadOwner(ThreadID threadID, PanelID panelID);

    // TODO: Remove this
    bool isThreadsWithCameraNullptr();

    // Calibration Helper Methods
    bool isCalibrationThreadRunning();
    bool isCalibrationThreadOwner(PanelID panelID);
    BaseCalibrationThread *getRunningCalibrationThread();

    // Manual Calibration Helper Methods
    bool isManualCalibrationThreadRunning();
    bool isManualCalibrationThreadOwner(PanelID panelID);
    BaseManualCalibrationThread *getRunningManualCalibrationThread();

    // Calibration Preview Helper Methods
    bool isCalibPreviewThreadRunning();

    // Capture Helper Methods
    bool isCapturePanelThreadRunning();

    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    CaptureThread *getCaptureThread();

    LoadCaptureThread *getLoadCaptureThread();

    LoadFileThread *getLoadFileThread();

    SaveDataThread *getSaveFileThread();

    ReplayThread *getReplayThread();

    CalibrationThread *getCalibrationThread();

    CaptureCalibrationThread *getCaptureCalibrationThread();

    CalibPreviewThread *getCalibPreviewThread();

    CalibCapturePreviewThread *getCalibCapturePreviewThread();

    ManualCalibrationThread *getManualCalibrationThread();

    ManualCalibrationCaptureThread *getManualCalibrationCaptureThread();

    ColorCalibrationThread *getColorCalibrationThread();

    ColorCalibPreviewThread *getColorCalibPreviewThread();

    ResultPreviewThread *getResultPreviewThread();

    RoiThread *getRoiThread();

    RoiPreviewThread *getRoiPreviewThread();

    ProcessThread *getProcessThread();

    TrimDataThread *getTrimDataThread();

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

    SaveDataThread *saveFileThread;

    ReplayThread *replayThread;

    CalibrationThread *calibrationThread;

    CaptureCalibrationThread *captureCalibrationThread;

    CalibPreviewThread *calibPreviewThread;

    CalibCapturePreviewThread *calibCapturePreviewThread;

    ManualCalibrationThread *manualCalibrationThread;

    ManualCalibrationCaptureThread *manualCalibrationCaptureThread;

    ColorCalibrationThread *colorCalibrationThread;

    ColorCalibPreviewThread *colorCalibPreviewThread;

    RoiThread *roiThread;

    RoiPreviewThread *roiPreviewThread;

    ProcessThread *processThread;

    ResultPreviewThread *resultPreviewThread;

    TrimDataThread *trimDataThread;
};