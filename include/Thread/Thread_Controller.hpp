#pragma once

#include <Model/SessionData.hpp>
#include <Thread/Thread_CalibrationPreviewCamera.hpp>
#include <Thread/Thread_CalibrationPreviewCapture.hpp>
#include <Thread/Thread_CameraPreview.hpp>
#include <Thread/Thread_CapturePreview.hpp>
#include <Thread/Thread_ColorCalibration.hpp>
#include <Thread/Thread_ColorCalibrationPreview.hpp>
#include <Thread/Thread_DistanceCalibrationCamera.hpp>
#include <Thread/Thread_DistanceCalibrationCapture.hpp>
#include <Thread/Thread_LaneCalibrationCamera.hpp>
#include <Thread/Thread_LaneCalibrationCapture.hpp>
#include <Thread/Thread_LaneManualCalibrationCamera.hpp>
#include <Thread/Thread_LaneManualCalibrationCapture.hpp>
#include <Thread/Thread_LoadCapture.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <Thread/Thread_Process.hpp>
#include <Thread/Thread_ResultPreview.hpp>
#include <Thread/Thread_Roi.hpp>
#include <Thread/Thread_RoiPreview.hpp>
#include <Thread/Thread_SaveData.hpp>
#include <Thread/Thread_TrimData.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>

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

    virtual void
    startLaneCalibrationCameraHandler(wxEvtHandler *parent, DataPtr data,
                                      CameraPtr &camera, HSVFilterPtr hsvFilter,
                                      BFSPtr bfs, RansacLinePtr ransac,
                                      PanelID panelID);
    void endLaneCalibrationCameraHandler();

    virtual void
    startLaneCalibrationCaptureHandler(wxEvtHandler *parent, DataPtr data,
                                       HSVFilterPtr hsvFilter, BFSPtr bfs,
                                       RansacLinePtr ransac, PanelID panelID);

    void endLaneCalibrationCaptureHandler();

    virtual void startCalibrationPreviewCameraHandler(wxEvtHandler *parent,
                                                      CameraPtr &camera,
                                                      DataPtr data,
                                                      PanelID panelID);

    void endCalibrationPreviewCameraHandler();

    virtual void startCalibrationPreviewCaptureHandler(wxEvtHandler *parent,
                                                       DataPtr data,
                                                       PanelID panelID);

    void endCalibrationPreviewCaptureHandler();

    virtual void startLaneManualCalibrationCameraHandler(wxEvtHandler *parent,
                                                         CameraPtr &camera,
                                                         PanelID panelID);

    void endLaneManualCalibrationCameraHandler();

    virtual void startManualCalibrationCaptureHandler(wxEvtHandler *parent,
                                                      DataPtr data,
                                                      PanelID panelID);

    void endManualCalibrationCaptureHandler();

    virtual void startDistaneCalibrationCameraHandler(wxEvtHandler *parent,
                                                      CameraPtr &camera,
                                                      PanelID panelID);

    void endDistanceCalibrationCameraHandler();

    virtual void startDistanceCalibrationCaptureHandler(wxEvtHandler *parent,
                                                        DataPtr data,
                                                        PanelID panelID);

    void endDistanceCalibrationCaptureHandler();

    virtual void startColorCalibrationHandler(wxEvtHandler *parent,
                                              DataPtr data, CameraPtr &camera,
                                              HSVFilterPtr hsvFilter,
                                              BFSPtr bfs, PanelID panelID);
    void endColorCalibrationHandler();

    virtual void startColorCalibrationPreviewHandler(
        wxEvtHandler *parent, CameraPtr &camera, const ColorRange &blueRange,
        const ColorRange &yellowRange, PanelID panelID);

    void endColorCalibrationPreviewHandler();

    virtual void startRoiHandler(wxEvtHandler *parent, DataPtr data,
                                 PanelID panelID);

    void endRoiHandler();

    virtual void startRoiPreviewHandler(wxEvtHandler *parent, DataPtr data,
                                        PanelID panelID);

    void endRoiPreviewHandler();

    virtual void startProcessHandler(wxEvtHandler *parent, POOLPtr threadPool,
                                     DataPtr data, DetectorPtr detector,
                                     TrackerPtr tracker, SpeedCalcPtr speedCalc,
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

    // Lane Calibration Helper Methods
    bool isLaneCalibrationThreadRunning();
    bool isLaneCalibrationThreadOwner(PanelID panelID);
    BaseLaneCalibrationThread *getRunningLaneCalibrationThread();

    // Lane Manual Calibration Helper Methods
    bool isLaneManualCalibrationThreadRunning();
    bool isLaneManualCalibrationThreadOwner(PanelID panelID);
    BaseLaneManualCalibrationThread *getRunningLaneManualCalibrationThread();

    // Distance Calibration Helper Methods
    bool isDistanceCalibrationThreadRunning();
    bool isDistanceCalibrationThreadOwner(PanelID panelID);
    BaseDistanceCalibrationThread *getRunningDistanceCalibrationThread();

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

    LaneCalibrationCameraThread *getLaneCalibrationCameraThread();

    LaneCalibrationCaptureThread *getLaneCalibrationCaptureThread();

    CalibrationPreviewCameraThread *getCalibrationPreviewCameraThread();

    CalibrationPreviewCaptureThread *getCalibrationPreviewCaptureThread();

    ManualCalibrationCameraThread *getLaneManualCalibrationCameraThread();

    LaneManualCalibrationCaptureThread *getLaneManualCalibrationCaptureThread();

    DistanceCalibrationCameraThread *getDistanceCalibrationCameraThread();

    DistanceCalibrationCaptureThread *getDistanceCalibrationCaptureThread();

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

    LaneCalibrationCameraThread *laneCalibrationCameraThread;

    LaneCalibrationCaptureThread *laneCalibrationCaptureThread;

    CalibrationPreviewCameraThread *calibrationPreviewCameraThread;

    CalibrationPreviewCaptureThread *calibrationPreviewCaptureThread;

    ManualCalibrationCameraThread *laneManualCalibrationCameraThread;

    LaneManualCalibrationCaptureThread *laneManualCalibrationCaptureThread;

    DistanceCalibrationCameraThread *distanceCalibrationCameraThread;

    DistanceCalibrationCaptureThread *distanceCalibrationCaptureThread;

    ColorCalibrationThread *colorCalibrationThread;

    ColorCalibrationPreviewThread *colorCalibPreviewThread;

    RoiThread *roiThread;

    RoiPreviewThread *roiPreviewThread;

    ProcessThread *processThread;

    ResultPreviewThread *resultPreviewThread;

    TrimDataThread *trimDataThread;
};