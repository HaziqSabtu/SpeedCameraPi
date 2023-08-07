#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_ColorCalibPreview.hpp"
#include "Thread/Thread_LoadCapture.hpp"
#include "Thread/Thread_Process.hpp"
#include "Thread/Thread_Result.hpp"
#include "Thread/Thread_Roi.hpp"
#include "Utils/DataStruct.hpp"
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
    replayThread = nullptr;
    calibrationThread = nullptr;
    calibPreviewThread = nullptr;
    manualCalibrationThread = nullptr;
    colorCalibrationThread = nullptr;
    colorCalibPreviewThread = nullptr;
    roiThread = nullptr;
    processThread = nullptr;
    resultPreviewThread = nullptr;
};

void ThreadController::deleteThread() {
    stopAndDeleteThread(captureThread);
    stopAndDeleteThread(loadCaptureThread);
    stopAndDeleteThread(loadFileThread);
    stopAndDeleteThread(replayThread);
    stopAndDeleteThread(calibrationThread);
    stopAndDeleteThread(calibPreviewThread);
    stopAndDeleteThread(manualCalibrationThread);
    stopAndDeleteThread(colorCalibrationThread);
    stopAndDeleteThread(colorCalibPreviewThread);
    stopAndDeleteThread(roiThread);
    stopAndDeleteThread(processThread);
    stopAndDeleteThread(resultPreviewThread);
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

    if (threadID == ThreadID::THREAD_REPLAY) {
        return replayThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION) {
        return calibrationThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW) {
        return calibPreviewThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_MANUAL_CALIBRATION) {
        return manualCalibrationThread == nullptr;
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

    if (threadID == ThreadID::THREAD_PROCESS) {
        return processThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_RESULT_PREVIEW) {
        return resultPreviewThread == nullptr;
    }

    throw std::runtime_error(
        "ThreadController::isThreadNullptr() - Invalid ThreadID");
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
    const int maxFrame, PanelID panelID) {

    loadCaptureThread = new LoadCaptureThread(parent, camera, data, maxFrame);
    loadCaptureThread->Run();

    owner[loadCaptureThread->getID()] = panelID;
}

void ThreadController::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

void ThreadController::startReplayHandler(
    wxEvtHandler *parent, std::shared_ptr<std::vector<ImageData>> imgData,
    PanelID panelID) {

    replayThread = new ReplayThread(parent, imgData);
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

ReplayThread *ThreadController::getReplayThread() { return replayThread; }

CalibrationThread *ThreadController::getCalibrationThread() {
    return calibrationThread;
}

CalibPreviewThread *ThreadController::getCalibPreviewThread() {
    return calibPreviewThread;
}

ManualCalibrationThread *ThreadController::getManualCalibrationThread() {
    return manualCalibrationThread;
}

ColorCalibrationThread *ThreadController::getColorCalibrationThread() {
    return colorCalibrationThread;
}

ColorCalibPreviewThread *ThreadController::getColorCalibPreviewThread() {
    return colorCalibPreviewThread;
}

RoiThread *ThreadController::getRoiThread() { return roiThread; }

void ThreadController::startLoadFileHandler(wxEvtHandler *parent, int maxFrame,
                                            std::string path, PanelID panelID) {

    // loadFileThread = new LoadFileThread(parent, maxFrame, path);
    // loadFileThread->Run();

    // owner[loadFileThread->getID()] = panelID;
    throw std::runtime_error("Not Implemented");
}

void ThreadController::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
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

void ThreadController::startRoiHandler(wxEvtHandler *parent,
                                       ImageDataPtr imageData,
                                       PanelID panelID) {
    roiThread = new RoiThread(parent, imageData);
    roiThread->Run();

    owner[roiThread->getID()] = panelID;
}

void ThreadController::endRoiHandler() {
    roiThread = stopAndDeleteThread(roiThread);
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
