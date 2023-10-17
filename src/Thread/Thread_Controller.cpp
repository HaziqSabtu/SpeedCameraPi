#include <Thread/Thread_Controller.hpp>

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
    laneCalibrationCameraThread = nullptr;
    laneCalibrationCaptureThread = nullptr;
    calibrationPreviewCameraThread = nullptr;
    calibrationPreviewCaptureThread = nullptr;
    laneManualCalibrationCameraThread = nullptr;
    laneManualCalibrationCaptureThread = nullptr;
    distanceCalibrationCameraThread = nullptr;
    distanceCalibrationCaptureThread = nullptr;
    colorCalibrationThread = nullptr;
    colorCalibPreviewThread = nullptr;
    roiThread = nullptr;
    roiPreviewThread = nullptr;
    processThread = nullptr;
    resultPreviewThread = nullptr;
    trimDataThread = nullptr;
};

void ThreadController::deleteThread() {
    stopAndDeleteThread(cameraPreviewThread);
    stopAndDeleteThread(loadCaptureThread);
    stopAndDeleteThread(loadFileThread);
    stopAndDeleteThread(saveFileThread);
    stopAndDeleteThread(capturePreviewThread);
    stopAndDeleteThread(laneCalibrationCameraThread);
    stopAndDeleteThread(laneCalibrationCaptureThread);
    stopAndDeleteThread(calibrationPreviewCameraThread);
    stopAndDeleteThread(calibrationPreviewCaptureThread);
    stopAndDeleteThread(laneManualCalibrationCameraThread);
    stopAndDeleteThread(laneManualCalibrationCaptureThread);
    stopAndDeleteThread(distanceCalibrationCameraThread);
    stopAndDeleteThread(distanceCalibrationCaptureThread);
    stopAndDeleteThread(colorCalibrationThread);
    stopAndDeleteThread(colorCalibPreviewThread);
    stopAndDeleteThread(roiThread);
    stopAndDeleteThread(roiPreviewThread);
    stopAndDeleteThread(processThread);
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

    if (threadID == ThreadID::THREAD_LANE_CALIBRATION_CAMERA) {
        return laneCalibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LANE_CALIBRATION_CAPTURE) {
        return laneCalibrationCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW_CAMERA) {
        return calibrationPreviewCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_CALIBRATION_PREVIEW_CAPTURE) {
        return calibrationPreviewCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAMERA) {
        return laneManualCalibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAPTURE) {
        return laneManualCalibrationCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_DISTANCE_CALIBRATION_CAMERA) {
        return distanceCalibrationCameraThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_DISTANCE_CALIBRATION_CAPTURE) {
        return distanceCalibrationCaptureThread == nullptr;
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

bool ThreadController::isLaneCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isLaneCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_LANE_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_LANE_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseLaneCalibrationThread *ThreadController::getRunningLaneCalibrationThread() {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return getLaneCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return getLaneCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isLaneManualCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isLaneManualCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseLaneManualCalibrationThread *
ThreadController::getRunningLaneManualCalibrationThread() {

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        return getLaneManualCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        return getLaneManualCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isDistanceCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

bool ThreadController::isDistanceCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

BaseDistanceCalibrationThread *
ThreadController::getRunningDistanceCalibrationThread() {

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        return getDistanceCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        return getDistanceCalibrationCaptureThread();
    }

    return nullptr;
}

bool ThreadController::isProcessThreadRunning() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return true;
    }

    return false;
}

bool ThreadController::isProcessThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return isThreadOwner(THREAD_PROCESS, panelID);
    }

    return false;
}

BaseThread *ThreadController::getRunningProcessThread() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return getProcessThread();
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

bool ThreadController::isCalibPreviewThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAPTURE, panelID);
    }

    return false;
}

BaseThread *ThreadController::getRunningCalibPreviewThread() {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return getCalibrationPreviewCameraThread();
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return getCalibrationPreviewCaptureThread();
    }

    return nullptr;
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

LaneCalibrationCameraThread *
ThreadController::getLaneCalibrationCameraThread() {
    return laneCalibrationCameraThread;
}

LaneCalibrationCaptureThread *
ThreadController::getLaneCalibrationCaptureThread() {
    return laneCalibrationCaptureThread;
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
ThreadController::getLaneManualCalibrationCameraThread() {
    return laneManualCalibrationCameraThread;
}

LaneManualCalibrationCaptureThread *
ThreadController::getLaneManualCalibrationCaptureThread() {
    return laneManualCalibrationCaptureThread;
}

DistanceCalibrationCameraThread *
ThreadController::getDistanceCalibrationCameraThread() {
    return distanceCalibrationCameraThread;
}

DistanceCalibrationCaptureThread *
ThreadController::getDistanceCalibrationCaptureThread() {
    return distanceCalibrationCaptureThread;
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

void ThreadController::startLaneCalibrationCameraHandler(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera,
    HSVFilterPtr hsvFilter, BFSPtr bfs, RansacLinePtr ransac, PanelID panelID) {

    laneCalibrationCameraThread = new LaneCalibrationCameraThread(
        parent, data, camera, hsvFilter, bfs, ransac);
    laneCalibrationCameraThread->Run();

    owner[laneCalibrationCameraThread->getID()] = panelID;
}

void ThreadController::endLaneCalibrationCameraHandler() {
    laneCalibrationCameraThread =
        stopAndDeleteThread(laneCalibrationCameraThread);
}

void ThreadController::startLaneCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, HSVFilterPtr hsvFilter, BFSPtr bfs,
    RansacLinePtr ransac, PanelID panelID) {

    laneCalibrationCaptureThread =
        new LaneCalibrationCaptureThread(parent, data, hsvFilter, bfs, ransac);
    laneCalibrationCaptureThread->Run();

    owner[laneCalibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endLaneCalibrationCaptureHandler() {
    laneCalibrationCaptureThread =
        stopAndDeleteThread(laneCalibrationCaptureThread);
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

void ThreadController::startLaneManualCalibrationCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, PanelID panelID) {

    laneManualCalibrationCameraThread =
        new ManualCalibrationCameraThread(parent, camera);
    laneManualCalibrationCameraThread->Run();

    owner[laneManualCalibrationCameraThread->getID()] = panelID;
}

void ThreadController::endLaneManualCalibrationCameraHandler() {
    laneManualCalibrationCameraThread =
        stopAndDeleteThread(laneManualCalibrationCameraThread);
}

void ThreadController::startManualCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    laneManualCalibrationCaptureThread =
        new LaneManualCalibrationCaptureThread(parent, data);
    laneManualCalibrationCaptureThread->Run();

    owner[laneManualCalibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endManualCalibrationCaptureHandler() {
    laneManualCalibrationCaptureThread =
        stopAndDeleteThread(laneManualCalibrationCaptureThread);
}

void ThreadController::startDistaneCalibrationCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, PanelID panelID) {

    distanceCalibrationCameraThread =
        new DistanceCalibrationCameraThread(parent, camera);
    distanceCalibrationCameraThread->Run();

    owner[distanceCalibrationCameraThread->getID()] = panelID;
}

void ThreadController::endDistanceCalibrationCameraHandler() {
    distanceCalibrationCameraThread =
        stopAndDeleteThread(distanceCalibrationCameraThread);
}

void ThreadController::startDistanceCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    distanceCalibrationCaptureThread =
        new DistanceCalibrationCaptureThread(parent, data);
    distanceCalibrationCaptureThread->Run();

    owner[distanceCalibrationCaptureThread->getID()] = panelID;
}

void ThreadController::endDistanceCalibrationCaptureHandler() {
    distanceCalibrationCaptureThread =
        stopAndDeleteThread(distanceCalibrationCaptureThread);
}

void ThreadController::startColorCalibrationHandler(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera,
    HSVFilterPtr hsvFilter, BFSPtr bfs, PanelID panelID) {

    colorCalibrationThread =
        new ColorCalibrationThread(parent, data, camera, hsvFilter, bfs);
    colorCalibrationThread->Run();

    owner[colorCalibrationThread->getID()] = panelID;
}

void ThreadController::endColorCalibrationHandler() {
    colorCalibrationThread = stopAndDeleteThread(colorCalibrationThread);
}

void ThreadController::startColorCalibrationPreviewHandler(
    wxEvtHandler *parent, CameraPtr &camera, const ColorRange &blueRange,
    const ColorRange &yellowRange, PanelID panelID) {
    colorCalibPreviewThread = new ColorCalibrationPreviewThread(
        parent, camera, blueRange, yellowRange);
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
                                           DetectorPtr detector,
                                           TrackerPtr tracker,
                                           SpeedCalcPtr speedCalc,
                                           PanelID panelID) {
    processThread = new ProcessThread(parent, data, detector, tracker,
                                      speedCalc, threadPool);
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
//                                 CameraPtr &camera) {
//     return new CaptureThread(parent, camera);
// }
