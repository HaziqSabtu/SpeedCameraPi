#pragma once

#include "Model/ExtraModel.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_CalibrationCamera.hpp"
#include "Thread/Thread_CalibrationCapture.hpp"
#include "Thread/Thread_CalibrationPreviewCamera.hpp"
#include "Thread/Thread_CalibrationPreviewCapture.hpp"
#include "Thread/Thread_CameraPreview.hpp"
#include "Thread/Thread_CapturePreview.hpp"
#include "Thread/Thread_ColorCalibration.hpp"
#include "Thread/Thread_ColorCalibrationPreview.hpp"
#include "Thread/Thread_HorizontalCalibrationCamera.hpp"
#include "Thread/Thread_HorizontalCalibrationCapture.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Thread/Thread_ManualCalibrationCamera.hpp"
#include "Thread/Thread_ManualCalibrationCapture.hpp"
#include "Thread/Thread_Process.hpp"
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

    virtual void startCameraPreviewHandler(wxEvtHandler *parent,
                                           CameraPtr &camera, PanelID panelID);
    void endCameraPreviewHandler();

    virtual void startLoadCaptureHandler(wxEvtHandler *parent,
                                         CameraPtr &camera, DataPtr data,
                                         const int maxFrame,
                                         const bool Debug_ShowImage,
                                         const bool Debug_Save,
                                         PanelID panelID);
    void endLoadCaptureHandler();

    virtual void startLoadFileHandler(wxEvtHandler *parent, DataPtr data,
                                      std::string path, PanelID panelID);
    void endLoadFileHandler();

    virtual void startSaveFileHandler(wxEvtHandler *parent, DataPtr data,
                                      PanelID panelID);

    void endSaveFileHandler();

    virtual void startCapturePreviewHandler(wxEvtHandler *parent, DataPtr data,
                                            PanelID panelID);
    void endCapturePreviewHandler();

    virtual void startCalibrationCameraHandler(wxEvtHandler *parent,
                                               CameraPtr &camera,
                                               PanelID panelID);
    void endCalibrationCameraHandler();

    virtual void startCalibrationCaptureHandler(wxEvtHandler *parent,
                                                DataPtr data, PanelID panelID);

    void endCalibrationCaptureHandler();

    virtual void startCalibrationPreviewCameraHandler(wxEvtHandler *parent,
                                                      CameraPtr &camera,
                                                      DataPtr data,
                                                      PanelID panelID);

    void endCalibrationPreviewCameraHandler();

    virtual void startCalibrationPreviewCaptureHandler(wxEvtHandler *parent,
                                                       DataPtr data,
                                                       PanelID panelID);

    void endCalibrationPreviewCaptureHandler();

    virtual void startManualCalibrationCameraHandler(wxEvtHandler *parent,
                                                     CameraPtr &camera,
                                                     PanelID panelID);

    void endManualCalibrationCameraHandler();

    virtual void startManualCalibrationCaptureHandler(wxEvtHandler *parent,
                                                      DataPtr data,
                                                      PanelID panelID);

    void endManualCalibrationCaptureHandler();

    virtual void startHorizontalCalibrationCameraHandler(wxEvtHandler *parent,
                                                         CameraPtr &camera,
                                                         PanelID panelID);

    void endHorizontalCalibrationCameraHandler();

    virtual void startHorizontalCalibrationCaptureHandler(wxEvtHandler *parent,
                                                          DataPtr data,
                                                          PanelID panelID);

    void endHorizontalCalibrationCaptureHandler();

    virtual void startColorCalibrationHandler(wxEvtHandler *parent,
                                              CameraPtr &camera,
                                              PanelID panelID);
    void endColorCalibrationHandler();

    virtual void startColorCalibrationPreviewHandler(wxEvtHandler *parent,
                                                     CameraPtr &camera,
                                                     CCModelPtr ccExtraModel,
                                                     PanelID panelID);

    void endColorCalibrationPreviewHandler();

    virtual void startRoiHandler(wxEvtHandler *parent, DataPtr data,
                                 PanelID panelID);

    void endRoiHandler();

    virtual void startRoiPreviewHandler(wxEvtHandler *parent, DataPtr data,
                                        PanelID panelID);

    void endRoiPreviewHandler();

    virtual void startProcessHandler(wxEvtHandler *parent, POOLPtr threadPool,
                                     DataPtr data, DetectorPtr detector,
                                     TrackerPtr tracker, SpeedPtr speedCalc,
                                     PanelID panelID);

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

    // Calibration Helper Methods
    bool isCalibrationThreadRunning();
    bool isCalibrationThreadOwner(PanelID panelID);
    BaseCalibrationThread *getRunningCalibrationThread();

    // Manual Calibration Helper Methods
    bool isManualCalibrationThreadRunning();
    bool isManualCalibrationThreadOwner(PanelID panelID);
    BaseManualCalibrationThread *getRunningManualCalibrationThread();

    // Horizontal Calibration Helper Methods
    bool isHorizontalCalibrationThreadRunning();
    bool isHorizontalCalibrationThreadOwner(PanelID panelID);
    BaseHorizontalCalibrationThread *getRunningHorizontalCalibrationThread();

    // Calibration Preview Helper Methods
    bool isCalibPreviewThreadRunning();
    bool isCalibPreviewThreadOwner(PanelID panelID);
    BaseThread *getRunningCalibPreviewThread();

    // Capture Helper Methods
    bool isCapturePanelThreadRunning();

    // Process Helper Methods
    bool isProcessThreadRunning();
    bool isProcessThreadOwner(PanelID panelID);
    BaseThread *getRunningProcessThread();

    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////
    ////////////////////////////////

    CameraPreviewThread *getCameraPreviewThread();

    LoadCaptureThread *getLoadCaptureThread();

    LoadFileThread *getLoadFileThread();

    SaveDataThread *getSaveFileThread();

    CapturePreviewThread *getCapturePreviewThread();

    CalibrationCameraThread *getCalibrationCameraThread();

    CalibrationCaptureThread *getCalibrationCaptureThread();

    CalibrationPreviewCameraThread *getCalibrationPreviewCameraThread();

    CalibrationPreviewCaptureThread *getCalibrationPreviewCaptureThread();

    ManualCalibrationCameraThread *getManualCalibrationCameraThread();

    ManualCalibrationCaptureThread *getManualCalibrationCaptureThread();

    HorizontalCalibrationCameraThread *getHorizontalCalibrationCameraThread();

    HorizontalCalibrationCaptureThread *getHorizontalCalibrationCaptureThread();

    ColorCalibrationThread *getColorCalibrationThread();

    ColorCalibrationPreviewThread *getColorCalibPreviewThread();

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

    CameraPreviewThread *cameraPreviewThread;

    LoadCaptureThread *loadCaptureThread;

    LoadFileThread *loadFileThread;

    SaveDataThread *saveFileThread;

    CapturePreviewThread *capturePreviewThread;

    CalibrationCameraThread *calibrationCameraThread;

    CalibrationCaptureThread *calibrationCaptureThread;

    CalibrationPreviewCameraThread *calibrationPreviewCameraThread;

    CalibrationPreviewCaptureThread *calibrationPreviewCaptureThread;

    ManualCalibrationCameraThread *manualCalibrationCameraThread;

    ManualCalibrationCaptureThread *manualCalibrationCaptureThread;

    HorizontalCalibrationCameraThread *horizontalCalibrationCameraThread;

    HorizontalCalibrationCaptureThread *horizontalCalibrationCaptureThread;

    ColorCalibrationThread *colorCalibrationThread;

    ColorCalibrationPreviewThread *colorCalibPreviewThread;

    RoiThread *roiThread;

    RoiPreviewThread *roiPreviewThread;

    ProcessThread *processThread;

    ResultPreviewThread *resultPreviewThread;

    TrimDataThread *trimDataThread;
};