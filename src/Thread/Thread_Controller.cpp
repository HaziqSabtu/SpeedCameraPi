#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_CalibPreviewCapture.hpp"
#include "Thread/Thread_CalibrationCapture.hpp"
#include "Thread/Thread_ColorCalibPreview.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_ManualCalibCapture.hpp"
#include "Thread/Thread_Process.hpp"
#include "Thread/Thread_ResultPreview.hpp"
#include "Thread/Thread_Roi.hpp"
#include "Thread/Thread_SaveData.hpp"
#include <Thread/Thread_Controller.hpp>
#include <Thread/Thread_ManualCalib.hpp>

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
    captureThread = nullptr;
    loadCaptureThread = nullptr;
    loadFileThread = nullptr;
    saveFileThread = nullptr;
    replayThread = nullptr;
    calibrationThread = nullptr;
    captureCalibrationThread = nullptr;
    calibPreviewThread = nullptr;
    calibCapturePreviewThread = nullptr;
    manualCalibrationThread = nullptr;
    manualCalibrationCaptureThread = nullptr;
    colorCalibrationThread = nullptr;
    colorCalibPreviewThread = nullptr;
    roiThread = nullptr;
    roiPreviewThread = nullptr;
    processThread = nullptr;
    resultPreviewThread = nullptr;
    trimDataThread = nullptr;
};

void ThreadController::deleteThread() {
    stopAndDeleteThread(captureThread);
    stopAndDeleteThread(loadCaptureThread);
    stopAndDeleteThread(loadFileThread);
    stopAndDeleteThread(saveFileThread);
    stopAndDeleteThread(replayThread);
    stopAndDeleteThread(calibrationThread);
    stopAndDeleteThread(captureCalibrationThread);
    stopAndDeleteThread(calibPreviewThread);
    stopAndDeleteThread(calibCapturePreviewThread);
    stopAndDeleteThread(manualCalibrationThread);
    stopAndDeleteThread(manualCalibrationCaptureThread);
    stopAndDeleteThread(colorCalibrationThread);
    stopAndDeleteThread(colorCalibPreviewThread);
    stopAndDeleteThread(roiThread);
    stopAndDeleteThread(roiPreviewThread);
    stopAndDeleteThread(processThread);
    stopAndDeleteThread(resultPreviewThread);
    stopAndDeleteThread(trimDataThread);
};

bool ThreadController::isThreadNullptr(ThreadID threadID) {
    if (threadID == ThreadID::THREAD_CAPTURE) {
        return captureThread == nullptr;
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

    if (threadID == ThreadID::THREAD_REPLAY) {
        return replayThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION) {
        return calibrationThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_CAPTURE) {
        return captureCalibrationThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW) {
        return calibPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW_CAPTURE) {
        return calibCapturePreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_MANUAL_CALIBRATION) {
        return manualCalibrationThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_MANUAL_CALIBRATION_CAPTURE) {
        return manualCalibrationCaptureThread == nullptr;
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

bool ThreadController::isThreadsWithCameraNullptr() {
    return captureThread == nullptr && loadCaptureThread == nullptr &&
           loadFileThread == nullptr && calibrationThread == nullptr &&
           calibPreviewThread == nullptr &&
           manualCalibrationThread == nullptr &&
           colorCalibrationThread == nullptr &&
           colorCalibPreviewThread == nullptr;
}

bool ThreadController::isCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_CALIBRATION)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_CALIBRATION)) {
        return isThreadOwner(THREAD_CALIBRATION, panelID);
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseCalibrationThread *ThreadController::getRunningCalibrationThread() {

    if (!isThreadNullptr(THREAD_CALIBRATION)) {
        return getCalibrationThread();
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_CAPTURE)) {
        return getCaptureCalibrationThread();
    }

    return nullptr;
}

bool ThreadController::isManualCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isManualCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return isThreadOwner(THREAD_MANUAL_CALIBRATION, panelID);
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_MANUAL_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseManualCalibrationThread *
ThreadController::getRunningManualCalibrationThread() {

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        return getManualCalibrationThread();
    }

    if (!isThreadNullptr(THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        return getManualCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isCalibPreviewThreadRunning() {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isCapturePanelThreadRunning() {

    if (!isThreadNullptr(THREAD_CAPTURE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LOAD_FILE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_SAVE_FILE)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_REPLAY)) {
        return true;
    }

    return false;
}

void ThreadController::startCaptureHandler(wxEvtHandler *parent,
                                           std::unique_ptr<CameraBase> &camera,
                                           PanelID panelID) {

    captureThread = new CaptureThread(parent, camera);
    captureThread->Run();

    owner[captureThread->getID()] = panelID;
}

void ThreadController::endCaptureHandler() {
    captureThread = stopAndDeleteThread(captureThread);
}

void ThreadController::startLoadCaptureHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera, DataPtr data,
    const int maxFrame, const bool Debug_ShowImage, const bool Debug_Save,
    PanelID panelID) {

    loadCaptureThread = new LoadCaptureThread(parent, camera, data, maxFrame,
                                              Debug_ShowImage, Debug_Save);
    loadCaptureThread->Run();

    owner[loadCaptureThread->getID()] = panelID;
}

void ThreadController::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

void ThreadController::startReplayHandler(wxEvtHandler *parent, DataPtr data,
                                          PanelID panelID) {

    replayThread = new ReplayThread(parent, data);
    replayThread->Run();

    owner[replayThread->getID()] = panelID;
}

void ThreadController::endReplayHandler() {
    replayThread = stopAndDeleteThread(replayThread);
}

CaptureThread *ThreadController::getCaptureThread() { return captureThread; }

LoadCaptureThread *ThreadController::getLoadCaptureThread() {
    return loadCaptureThread;
}

LoadFileThread *ThreadController::getLoadFileThread() { return loadFileThread; }

SaveDataThread *ThreadController::getSaveFileThread() { return saveFileThread; }

ReplayThread *ThreadController::getReplayThread() { return replayThread; }

CalibrationThread *ThreadController::getCalibrationThread() {
    return calibrationThread;
}

CaptureCalibrationThread *ThreadController::getCaptureCalibrationThread() {
    return captureCalibrationThread;
}

CalibPreviewThread *ThreadController::getCalibPreviewThread() {
    return calibPreviewThread;
}

CalibCapturePreviewThread *ThreadController::getCalibCapturePreviewThread() {
    return calibCapturePreviewThread;
}

ManualCalibrationThread *ThreadController::getManualCalibrationThread() {
    return manualCalibrationThread;
}

ManualCalibrationCaptureThread *
ThreadController::getManualCalibrationCaptureThread() {
    return manualCalibrationCaptureThread;
}

ColorCalibrationThread *ThreadController::getColorCalibrationThread() {
    return colorCalibrationThread;
}

ColorCalibPreviewThread *ThreadController::getColorCalibPreviewThread() {
    return colorCalibPreviewThread;
}

RoiThread *ThreadController::getRoiThread() { return roiThread; }

RoiPreviewThread *ThreadController::getRoiPreviewThread() {
    return roiPreviewThread;
}

ProcessThread *ThreadController::getProcessThread() { return processThread; }

ResultPreviewThread *ThreadController::getResultPreviewThread() {
    return resultPreviewThread;
}

TrimDataThread *ThreadController::getTrimDataThread() { return trimDataThread; }

void ThreadController::startLoadFileHandler(wxEvtHandler *parent, DataPtr data,
                                            int maxFrame, std::string path,
                                            PanelID panelID) {

    loadFileThread = new LoadFileThread(parent, data, path, maxFrame);
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

void ThreadController::startCalibrationHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    PanelID panelID) {

    calibrationThread = new CalibrationThread(parent, camera);
    calibrationThread->Run();

    owner[calibrationThread->getID()] = panelID;
}

void ThreadController::endCalibrationHandler() {
    calibrationThread = stopAndDeleteThread(calibrationThread);
}

void ThreadController::startCaptureCalibrationHandler(wxEvtHandler *parent,
                                                      DataPtr data,
                                                      PanelID panelID) {

    captureCalibrationThread = new CaptureCalibrationThread(parent, data);
    captureCalibrationThread->Run();

    owner[captureCalibrationThread->getID()] = panelID;
}

void ThreadController::endCaptureCalibrationHandler() {
    captureCalibrationThread = stopAndDeleteThread(captureCalibrationThread);
}

void ThreadController::startCalibPreviewHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    std::shared_ptr<SessionData> data, PanelID panelID) {
    calibPreviewThread = new CalibPreviewThread(parent, camera, data);
    calibPreviewThread->Run();

    owner[calibPreviewThread->getID()] = panelID;
}

void ThreadController::endCalibPreviewHandler() {
    calibPreviewThread = stopAndDeleteThread(calibPreviewThread);
}

void ThreadController::startCalibCapturePreviewHandler(wxEvtHandler *parent,
                                                       DataPtr data,
                                                       PanelID panelID) {
    calibCapturePreviewThread = new CalibCapturePreviewThread(parent, data);
    calibCapturePreviewThread->Run();

    owner[calibCapturePreviewThread->getID()] = panelID;
}

void ThreadController::endCalibCapturePreviewHandler() {
    calibCapturePreviewThread = stopAndDeleteThread(calibCapturePreviewThread);
}

void ThreadController::startManualCalibrationHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    PanelID panelID) {

    manualCalibrationThread = new ManualCalibrationThread(parent, camera);
    manualCalibrationThread->Run();

    owner[manualCalibrationThread->getID()] = panelID;
}

void ThreadController::endManualCalibrationHandler() {
    manualCalibrationThread = stopAndDeleteThread(manualCalibrationThread);
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

void ThreadController::startColorCalibrationHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    PanelID panelID) {

    colorCalibrationThread = new ColorCalibrationThread(parent, camera);
    colorCalibrationThread->Run();

    owner[colorCalibrationThread->getID()] = panelID;
}

void ThreadController::endColorCalibrationHandler() {
    colorCalibrationThread = stopAndDeleteThread(colorCalibrationThread);
}

void ThreadController::startColorCalibPreviewHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    std::shared_ptr<ColorCalibExtraModel> ccExtraModel, PanelID panelID) {
    colorCalibPreviewThread =
        new ColorCalibPreviewThread(parent, camera, ccExtraModel);
    colorCalibPreviewThread->Run();

    owner[colorCalibPreviewThread->getID()] = panelID;
}

void ThreadController::endColorCalibPreviewHandler() {
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
    processThread = new ProcessThread(parent, threadPool, data);
    processThread->Run();

    owner[processThread->getID()] = panelID;
}

void ThreadController::endProcessHandler() {
    processThread = stopAndDeleteThread(processThread);
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
//                                 std::unique_ptr<CameraBase> &camera) {
//     return new CaptureThread(parent, camera);
// }
