#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Thread/Thread_Controller.hpp>

#include <exception>
#include <iostream>
#include <memory>

ThreadController::ThreadController() { initThread(); }

ThreadController::~ThreadController() {
    try {
        deleteThread();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void ThreadController::initThread() {
    cameraPreviewThread = nullptr;
    loadCaptureThread = nullptr;
    loadFileThread = nullptr;
    saveFileThread = nullptr;
    capturePreviewThread = nullptr;
    calibrationCameraThread = nullptr;
    calibrationCaptureThread = nullptr;
    calibrationPreviewCameraThread = nullptr;
    calibrationPreviewCaptureThread = nullptr;
    manualCalibrationCameraThread = nullptr;
    manualCalibrationCaptureThread = nullptr;
    horizontalCalibrationCameraThread = nullptr;
    horizontalCalibrationCaptureThread = nullptr;
    colorCalibrationThread = nullptr;
    colorCalibPreviewThread = nullptr;
    roiThread = nullptr;
    roiPreviewThread = nullptr;
    processThread = nullptr;
    processRedundantThread = nullptr;
    processHorizontalThread = nullptr;
    resultPreviewThread = nullptr;
    trimDataThread = nullptr;
};

void ThreadController::deleteThread() {
    stopAndDeleteThread(cameraPreviewThread);
    stopAndDeleteThread(loadCaptureThread);
    stopAndDeleteThread(loadFileThread);
    stopAndDeleteThread(saveFileThread);
    stopAndDeleteThread(capturePreviewThread);
    stopAndDeleteThread(calibrationCameraThread);
    stopAndDeleteThread(calibrationCaptureThread);
    stopAndDeleteThread(calibrationPreviewCameraThread);
    stopAndDeleteThread(calibrationPreviewCaptureThread);
    stopAndDeleteThread(manualCalibrationCameraThread);
    stopAndDeleteThread(manualCalibrationCaptureThread);
    stopAndDeleteThread(horizontalCalibrationCameraThread);
    stopAndDeleteThread(horizontalCalibrationCaptureThread);
    stopAndDeleteThread(colorCalibrationThread);
    stopAndDeleteThread(colorCalibPreviewThread);
    stopAndDeleteThread(roiThread);
    stopAndDeleteThread(roiPreviewThread);
    stopAndDeleteThread(processThread);
    stopAndDeleteThread(processRedundantThread);
    stopAndDeleteThread(processHorizontalThread);
    stopAndDeleteThread(resultPreviewThread);
    stopAndDeleteThread(trimDataThread);
};

bool ThreadController::isThreadNullptr(ThreadID threadID) {
    if (threadID == ThreadID::THREAD_CAMERA_PREVIEW) {
        return cameraPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LOAD_CAPTURE) {
        return loadCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LOAD_FILE) {
        return loadFileThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_SAVE_FILE) {
        return saveFileThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CAPTURE_PREVIEW) {
        return capturePreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_CAMERA) {
        return calibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_CAPTURE) {
        return calibrationCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW_CAMERA) {
        return calibrationPreviewCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW_CAPTURE) {
        return calibrationPreviewCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_MANUAL_CALIBRATION_CAMERA) {
        return manualCalibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_MANUAL_CALIBRATION_CAPTURE) {
        return manualCalibrationCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_HORIZONTAL_CALIBRATION_CAMERA) {
        return horizontalCalibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_HORIZONTAL_CALIBRATION_CAPTURE) {
        return horizontalCalibrationCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_COLOR_CALIBRATION) {
        return colorCalibrationThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_COLOR_CALIBRATION_PREVIEW) {
        return colorCalibPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_ROI) {
        return roiThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_ROI_PREVIEW) {
        return roiPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_PROCESS) {
        return processThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_PROCESS_REDUNDANT) {
        return processRedundantThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_PROCESS_HORIZONTAL) {
        return processHorizontalThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_RESULT_PREVIEW) {
        return resultPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_TRIM_DATA) {
        return trimDataThread == nullptr;
    }

    throw std::runtime_error(
        "ThreadController::isThreadNullptr() - Invalid ThreadID");
}

bool ThreadController::isThreadRunning(ThreadID threadID) {
    return !isThreadNullptr(threadID);
}

bool ThreadController::isThreadOwner(ThreadID threadID, PanelID panelID) {
    if (owner.find(threadID) == owner.end()) {
        return false;
    }
    return owner[threadID] == panelID;
}

bool ThreadController::isCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseCalibrationThread *ThreadController::getRunningCalibrationThread() {

    if (!isThreadNullptr(THREAD_CALIBRATION_CAMERA)) {
        return getCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return getCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isManualCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isManualCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_MANUAL_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_MANUAL_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseManualCalibrationThread *
ThreadController::getRunningManualCalibrationThread() {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAMERA)) {
        return getManualCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return getManualCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isHorizontalCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isHorizontalCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_HORIZONTAL_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_HORIZONTAL_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseHorizontalCalibrationThread *
ThreadController::getRunningHorizontalCalibrationThread() {

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        return getHorizontalCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        return getHorizontalCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isProcessThreadRunning() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_PROCESS_REDUNDANT)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_PROCESS_HORIZONTAL)) {
        return true;
    }

    return false;
}

bool ThreadController::isProcessThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return isThreadOwner(THREAD_PROCESS, panelID);
    }

    if (!isThreadNullptr(THREAD_PROCESS_REDUNDANT)) {
        return isThreadOwner(THREAD_PROCESS_REDUNDANT, panelID);
    }

    if (!isThreadNullptr(THREAD_PROCESS_HORIZONTAL)) {
        return isThreadOwner(THREAD_PROCESS_HORIZONTAL, panelID);
    }

    return false;
}

BaseThread *ThreadController::getRunningProcessThread() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return getProcessThread();
    }

    if (!isThreadNullptr(THREAD_PROCESS_REDUNDANT)) {
        return getProcessRedundantThread();
    }

    if (!isThreadNullptr(THREAD_PROCESS_HORIZONTAL)) {
        return getProcessHorizontalThread();
    }

    return nullptr;
}

bool ThreadController::isCalibPreviewThreadRunning() {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isCapturePanelThreadRunning() {

    // if (!isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
    //     return true;
    // }

    if (!isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LOAD_FILE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_SAVE_FILE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        return true;
    }

    return false;
}

void ThreadController::startCameraPreviewHandler(wxEvtHandler *parent,
                                                 CameraPtr &camera,
                                                 PanelID panelID) {

    cameraPreviewThread = new CameraPreviewThread(parent, camera);
    cameraPreviewThread->Run();

    owner[cameraPreviewThread->getID()] = panelID;
}

void ThreadController::endCameraPreviewHandler() {
    cameraPreviewThread = stopAndDeleteThread(cameraPreviewThread);
}

void ThreadController::startLoadCaptureHandler(
    wxEvtHandler *parent, CameraPtr &camera, DataPtr data, const int maxFrame,
    const bool Debug_ShowImage, const bool Debug_Save, PanelID panelID) {

    loadCaptureThread = new LoadCaptureThread(parent, camera, data, maxFrame,
                                              Debug_ShowImage, Debug_Save);
    loadCaptureThread->Run();

    owner[loadCaptureThread->getID()] = panelID;
}

void ThreadController::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

void ThreadController::startCapturePreviewHandler(wxEvtHandler *parent,
                                                  DataPtr data,
                                                  PanelID panelID) {

    capturePreviewThread = new CapturePreviewThread(parent, data);
    capturePreviewThread->Run();

    owner[capturePreviewThread->getID()] = panelID;
}

void ThreadController::endCapturePreviewHandler() {
    capturePreviewThread = stopAndDeleteThread(capturePreviewThread);
}

CameraPreviewThread *ThreadController::getCameraPreviewThread() {
    return cameraPreviewThread;
}

LoadCaptureThread *ThreadController::getLoadCaptureThread() {
    return loadCaptureThread;
}

LoadFileThread *ThreadController::getLoadFileThread() { return loadFileThread; }

SaveDataThread *ThreadController::getSaveFileThread() { return saveFileThread; }

CapturePreviewThread *ThreadController::getCapturePreviewThread() {
    return capturePreviewThread;
}

CalibrationCameraThread *ThreadController::getCalibrationCameraThread() {
    return calibrationCameraThread;
}

CalibrationCaptureThread *ThreadController::getCalibrationCaptureThread() {
    return calibrationCaptureThread;
}

CalibrationPreviewCameraThread *
ThreadController::getCalibrationPreviewCameraThread() {
    return calibrationPreviewCameraThread;
}

CalibrationPreviewCaptureThread *
ThreadController::getCalibrationPreviewCaptureThread() {
    return calibrationPreviewCaptureThread;
}

ManualCalibrationCameraThread *
ThreadController::getManualCalibrationCameraThread() {
    return manualCalibrationCameraThread;
}

ManualCalibrationCaptureThread *
ThreadController::getManualCalibrationCaptureThread() {
    return manualCalibrationCaptureThread;
}

HorizontalCalibrationCameraThread *
ThreadController::getHorizontalCalibrationCameraThread() {
    return horizontalCalibrationCameraThread;
}

HorizontalCalibrationCaptureThread *
ThreadController::getHorizontalCalibrationCaptureThread() {
    return horizontalCalibrationCaptureThread;
}

ColorCalibrationThread *ThreadController::getColorCalibrationThread() {
    return colorCalibrationThread;
}

ColorCalibrationPreviewThread *ThreadController::getColorCalibPreviewThread() {
    return colorCalibPreviewThread;
}

RoiThread *ThreadController::getRoiThread() { return roiThread; }

RoiPreviewThread *ThreadController::getRoiPreviewThread() {
    return roiPreviewThread;
}

ProcessThread *ThreadController::getProcessThread() { return processThread; }

ProcessRedundantThread *ThreadController::getProcessRedundantThread() {
    return processRedundantThread;
}

ProcessHorizontalThread *ThreadController::getProcessHorizontalThread() {
    return processHorizontalThread;
}

ResultPreviewThread *ThreadController::getResultPreviewThread() {
    return resultPreviewThread;
}

TrimDataThread *ThreadController::getTrimDataThread() { return trimDataThread; }

void ThreadController::startLoadFileHandler(wxEvtHandler *parent, DataPtr data,
                                            std::string path, PanelID panelID) {

    loadFileThread = new LoadFileThread(parent, data, path);
    loadFileThread->Run();

    owner[loadFileThread->getID()] = panelID;
}

void ThreadController::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

void ThreadController::startSaveFileHandler(wxEvtHandler *parent, DataPtr data,
                                            PanelID panelID) {

    saveFileThread = new SaveDataThread(parent, data);
    saveFileThread->Run();

    owner[saveFileThread->getID()] = panelID;
}

void ThreadController::endSaveFileHandler() {
    saveFileThread = stopAndDeleteThread(saveFileThread);
}

void ThreadController::startCalibrationCameraHandler(wxEvtHandler *parent,
                                                     CameraPtr &camera,
                                                     PanelID panelID) {

    calibrationCameraThread = new CalibrationCameraThread(parent, camera);
    calibrationCameraThread->Run();

    owner[calibrationCameraThread->getID()] = panelID;
}

void ThreadController::endCalibrationCameraHandler() {
    calibrationCameraThread = stopAndDeleteThread(calibrationCameraThread);
}

void ThreadController::startCalibrationCaptureHandler(wxEvtHandler *parent,
                                                      DataPtr data,
                                                      PanelID panelID) {

    calibrationCaptureThread = new CalibrationCaptureThread(parent, data);
    calibrationCaptureThread->Run();

    owner[calibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endCalibrationCaptureHandler() {
    calibrationCaptureThread = stopAndDeleteThread(calibrationCaptureThread);
}

void ThreadController::startCalibrationPreviewCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, DataPtr data, PanelID panelID) {
    calibrationPreviewCameraThread =
        new CalibrationPreviewCameraThread(parent, data, camera);
    calibrationPreviewCameraThread->Run();

    owner[calibrationPreviewCameraThread->getID()] = panelID;
}

void ThreadController::endCalibrationPreviewCameraHandler() {
    calibrationPreviewCameraThread =
        stopAndDeleteThread(calibrationPreviewCameraThread);
}

void ThreadController::startCalibrationPreviewCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {
    calibrationPreviewCaptureThread =
        new CalibrationPreviewCaptureThread(parent, data);
    calibrationPreviewCaptureThread->Run();

    owner[calibrationPreviewCaptureThread->getID()] = panelID;
}

void ThreadController::endCalibrationPreviewCaptureHandler() {
    calibrationPreviewCaptureThread =
        stopAndDeleteThread(calibrationPreviewCaptureThread);
}

void ThreadController::startManualCalibrationCameraHandler(wxEvtHandler *parent,
                                                           CameraPtr &camera,
                                                           PanelID panelID) {

    manualCalibrationCameraThread =
        new ManualCalibrationCameraThread(parent, camera);
    manualCalibrationCameraThread->Run();

    owner[manualCalibrationCameraThread->getID()] = panelID;
}

void ThreadController::endManualCalibrationCameraHandler() {
    manualCalibrationCameraThread =
        stopAndDeleteThread(manualCalibrationCameraThread);
}

void ThreadController::startManualCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    manualCalibrationCaptureThread =
        new ManualCalibrationCaptureThread(parent, data);
    manualCalibrationCaptureThread->Run();

    owner[manualCalibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endManualCalibrationCaptureHandler() {
    manualCalibrationCaptureThread =
        stopAndDeleteThread(manualCalibrationCaptureThread);
}

void ThreadController::startHorizontalCalibrationCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, PanelID panelID) {

    horizontalCalibrationCameraThread =
        new HorizontalCalibrationCameraThread(parent, camera);
    horizontalCalibrationCameraThread->Run();

    owner[horizontalCalibrationCameraThread->getID()] = panelID;
}

void ThreadController::endHorizontalCalibrationCameraHandler() {
    horizontalCalibrationCameraThread =
        stopAndDeleteThread(horizontalCalibrationCameraThread);
}

void ThreadController::startHorizontalCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    horizontalCalibrationCaptureThread =
        new HorizontalCalibrationCaptureThread(parent, data);
    horizontalCalibrationCaptureThread->Run();

    owner[horizontalCalibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endHorizontalCalibrationCaptureHandler() {
    horizontalCalibrationCaptureThread =
        stopAndDeleteThread(horizontalCalibrationCaptureThread);
}

void ThreadController::startColorCalibrationHandler(wxEvtHandler *parent,
                                                    CameraPtr &camera,
                                                    PanelID panelID) {

    colorCalibrationThread = new ColorCalibrationThread(parent, camera);
    colorCalibrationThread->Run();

    owner[colorCalibrationThread->getID()] = panelID;
}

void ThreadController::endColorCalibrationHandler() {
    colorCalibrationThread = stopAndDeleteThread(colorCalibrationThread);
}

void ThreadController::startColorCalibrationPreviewHandler(
    wxEvtHandler *parent, CameraPtr &camera,
    std::shared_ptr<ColorCalibExtraModel> ccExtraModel, PanelID panelID) {
    colorCalibPreviewThread =
        new ColorCalibrationPreviewThread(parent, camera, ccExtraModel);
    colorCalibPreviewThread->Run();

    owner[colorCalibPreviewThread->getID()] = panelID;
}

void ThreadController::endColorCalibrationPreviewHandler() {
    colorCalibPreviewThread = stopAndDeleteThread(colorCalibPreviewThread);
}

void ThreadController::startRoiHandler(wxEvtHandler *parent, DataPtr data,
                                       PanelID panelID) {
    roiThread = new RoiThread(parent, data);
    roiThread->Run();

    owner[roiThread->getID()] = panelID;
}

void ThreadController::endRoiHandler() {
    roiThread = stopAndDeleteThread(roiThread);
}

void ThreadController::startRoiPreviewHandler(wxEvtHandler *parent,
                                              DataPtr data, PanelID panelID) {
    roiPreviewThread = new RoiPreviewThread(parent, data);
    roiPreviewThread->Run();

    owner[roiPreviewThread->getID()] = panelID;
}

void ThreadController::endRoiPreviewHandler() {
    roiPreviewThread = stopAndDeleteThread(roiPreviewThread);
}

void ThreadController::startProcessHandler(wxEvtHandler *parent,
                                           POOLPtr threadPool, DataPtr data,
                                           PanelID panelID) {
    processThread = new ProcessThread(parent, data, threadPool);
    processThread->Run();

    owner[processThread->getID()] = panelID;
}

void ThreadController::endProcessHandler() {
    processThread = stopAndDeleteThread(processThread);
}

void ThreadController::startProcessRedundantHandler(wxEvtHandler *parent,
                                                    POOLPtr threadPool,
                                                    DataPtr data,
                                                    PanelID panelID) {
    processRedundantThread =
        new ProcessRedundantThread(parent, data, threadPool);
    processRedundantThread->Run();

    owner[processRedundantThread->getID()] = panelID;
}

void ThreadController::endProcessRedundantHandler() {
    processRedundantThread = stopAndDeleteThread(processRedundantThread);
}

void ThreadController::startProcessHorizontalHandler(wxEvtHandler *parent,
                                                     POOLPtr threadPool,
                                                     DataPtr data,
                                                     PanelID panelID) {
    processHorizontalThread =
        new ProcessHorizontalThread(parent, data, threadPool);
    processHorizontalThread->Run();

    owner[processHorizontalThread->getID()] = panelID;
}

void ThreadController::endProcessHorizontalHandler() {
    processHorizontalThread = stopAndDeleteThread(processHorizontalThread);
}

void ThreadController::startResultPreviewHandler(wxEvtHandler *parent,
                                                 DataPtr data,
                                                 PanelID panelID) {
    resultPreviewThread = new ResultPreviewThread(parent, data);
    resultPreviewThread->Run();

    owner[resultPreviewThread->getID()] = panelID;
}

void ThreadController::endResultPreviewHandler() {
    resultPreviewThread = stopAndDeleteThread(resultPreviewThread);
}

void ThreadController::startTrimDataHandler(wxEvtHandler *parent, DataPtr data,
                                            PanelID panelID) {
    trimDataThread = new TrimDataThread(parent, data);
    trimDataThread->Run();

    owner[trimDataThread->getID()] = panelID;
}

void ThreadController::endTrimDataHandler() {
    trimDataThread = stopAndDeleteThread(trimDataThread);
}

template <typename T>
T *ThreadController::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}

void ThreadController::killAllThreads() { deleteThread(); }

// TODO: Cleanup
// Maybe Required for testing
// CaptureThread *
// CaptureModel::initCaptureThread(wxEvtHandler *parent,
//                                 CameraPtr &camera) {
//     return new CaptureThread(parent, camera);
// }
