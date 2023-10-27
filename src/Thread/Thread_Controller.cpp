#include <Thread/Thread_Controller.hpp>

/**
 * @brief Construct a new Thread Controller:: Thread Controller object
 *
 */
ThreadController::ThreadController() { initThread(); }

/**
 * @brief Destroy the Thread Controller:: Thread Controller object
 *
 */
ThreadController::~ThreadController() {
    try {
        deleteThread();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * @brief assign all threads to null
 *
 */
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

/**
 * @brief stop and delete the thread
 *
 * @return BaseThread* Pointer to the thread
 */
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

/**
 * @brief Check if the thread is running
 *
 * @param threadID The ThreadID of the thread
 * @return true If the thread is running
 * @return false If the thread is not running
 */
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

/**
 * @brief Check if the thread is running
 *
 * @param thread Pointer to the thread
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isThreadRunning(ThreadID threadID) {
    return !isThreadNullptr(threadID);
}

/**
 * @brief Check if current Panel Owns the thread. Owning means that the panel
 * starts the thread
 *
 * @param threadID The ThreadID of the thread
 * @param panelID The PanelID of the panel
 *
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isThreadOwner(ThreadID threadID, PanelID panelID) {
    if (owner.find(threadID) == owner.end()) {
        return false;
    }
    return owner[threadID] == panelID;
}

/**
 * @brief Check if LaneCalibrationThread is running
 *
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isLaneCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

/**
 * @brief Check if LaneCalibrationThread is owned by the current panel
 *
 * @param panelID The PanelID of the panel
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isLaneCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_LANE_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_LANE_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

/**
 * @brief Get the running LaneCalibrationThread
 *
 * @return BaseLaneCalibrationThread* Pointer to the thread
 */
BaseLaneCalibrationThread *ThreadController::getRunningLaneCalibrationThread() {

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAMERA)) {
        return getLaneCalibrationCameraThread();
    }

    if (!isThreadNullptr(THREAD_LANE_CALIBRATION_CAPTURE)) {
        return getLaneCalibrationCaptureThread();
    }

    return nullptr;
}

/**
 * @brief Check if ManualLaneCalibrationThread is running
 *
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isLaneManualCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

/**
 * @brief Check if ManualLaneCalibrationThread is owned by the current panel
 *
 * @param panelID The PanelID of the panel
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isLaneManualCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_LANE_MANUAL_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

/**
 * @brief Get the running ManualLaneCalibrationThread
 *
 * @return BaseLaneManualCalibrationThread* Pointer to the thread
 */
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

/**
 * @brief Check if DistanceCalibrationThread is running
 *
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isDistanceCalibrationThreadRunning() {

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        return true;
    }

    return false;
}

/**
 * @brief Check if DistanceCalibrationThread is owned by the current panel
 *
 * @param panelID The PanelID of the panel
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isDistanceCalibrationThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        return isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        return isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAPTURE, panelID);
    }

    return false;
}

/**
 * @brief Get the running DistanceCalibrationThread
 *
 * @return BaseDistanceCalibrationThread* Pointer to the thread
 */
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

/**
 * @brief Check if ProcessThread is running
 *
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isProcessThreadRunning() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return true;
    }

    return false;
}

/**
 * @brief Check if ProcessThread is owned by the current panel
 *
 * @param panelID The PanelID of the panel
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isProcessThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return isThreadOwner(THREAD_PROCESS, panelID);
    }

    return false;
}

/**
 * @brief Get the running ProcessThread
 *
 * @return BaseThread* Pointer to the thread
 */
BaseThread *ThreadController::getRunningProcessThread() {

    if (!isThreadNullptr(THREAD_PROCESS)) {
        return getProcessThread();
    }

    return nullptr;
}

/**
 * @brief Check if CalibrationPreviewThread is running
 *
 * @return true If the thread is running
 * @return false If the thread is not running
 */
bool ThreadController::isCalibPreviewThreadRunning() {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return true;
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return true;
    }

    return false;
}

/**
 * @brief Check if CalibrationPreviewThread is owned by the current panel
 *
 * @param panelID The PanelID of the panel
 * @return true If the panel owns the thread
 * @return false If the panel does not own the thread
 */
bool ThreadController::isCalibPreviewThreadOwner(PanelID panelID) {

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        return isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAMERA, panelID);
    }

    if (!isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        return isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAPTURE, panelID);
    }

    return false;
}

/**
 * @brief Get the running CalibrationPreviewThread
 *
 * @return BaseThread* Pointer to the thread
 */
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

/**
 * @brief Handle the start of the CameraPreviewThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param panelID PanelID of the panel
 */
void ThreadController::startCameraPreviewHandler(wxEvtHandler *parent,
                                                 CameraPtr &camera,
                                                 PanelID panelID) {

    cameraPreviewThread = new CameraPreviewThread(parent, camera);
    cameraPreviewThread->Run();

    owner[cameraPreviewThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the CameraPreviewThread
 *
 */
void ThreadController::endCameraPreviewHandler() {
    cameraPreviewThread = stopAndDeleteThread(cameraPreviewThread);
}

/**
 * @brief Handle the start of the LoadCaptureThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param data Pointer to the SessionData
 * @param maxFrame Maximum number of frames to capture
 * @param Debug_ShowImage Flag to show the captured image
 * @param Debug_Save Flag to save the captured image
 * @param panelID PanelID of the panel
 */
void ThreadController::startLoadCaptureHandler(
    wxEvtHandler *parent, CameraPtr &camera, DataPtr data, const int maxFrame,
    const bool Debug_ShowImage, const bool Debug_Save, PanelID panelID) {

    loadCaptureThread = new LoadCaptureThread(parent, camera, data, maxFrame,
                                              Debug_ShowImage, Debug_Save);
    loadCaptureThread->Run();

    owner[loadCaptureThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LoadCaptureThread
 *
 */
void ThreadController::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

/**
 * @brief Handle the start of the CapturePreviewThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startCapturePreviewHandler(wxEvtHandler *parent,
                                                  DataPtr data,
                                                  PanelID panelID) {

    capturePreviewThread = new CapturePreviewThread(parent, data);
    capturePreviewThread->Run();

    owner[capturePreviewThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the CapturePreviewThread
 *
 */
void ThreadController::endCapturePreviewHandler() {
    capturePreviewThread = stopAndDeleteThread(capturePreviewThread);
}

/**
 * @brief Get the CameraPreviewThread
 *
 * @return CameraPreviewThread*
 */
CameraPreviewThread *ThreadController::getCameraPreviewThread() {
    return cameraPreviewThread;
}

/**
 * @brief Get the LoadCaptureThread
 *
 * @return LoadCaptureThread*
 */
LoadCaptureThread *ThreadController::getLoadCaptureThread() {
    return loadCaptureThread;
}

/**
 * @brief Get the LoadFilteThread
 *
 * @return LoadFilteThread*
 */
LoadFileThread *ThreadController::getLoadFileThread() { return loadFileThread; }

/**
 * @brief Get the SaveDataThread
 *
 * @return SaveDataThread*
 */
SaveDataThread *ThreadController::getSaveFileThread() { return saveFileThread; }

/**
 * @brief Get the CapturePreviewThread
 *
 * @return CapturePreviewThread*
 */
CapturePreviewThread *ThreadController::getCapturePreviewThread() {
    return capturePreviewThread;
}

/**
 * @brief Get the LaneCalibrationCameraThread
 *
 * @return LaneCalibrationCameraThread*
 */
LaneCalibrationCameraThread *
ThreadController::getLaneCalibrationCameraThread() {
    return laneCalibrationCameraThread;
}

/**
 * @brief Get the LaneCalibrationCaptureThread
 *
 * @return LaneCalibrationCaptureThread*
 */
LaneCalibrationCaptureThread *
ThreadController::getLaneCalibrationCaptureThread() {
    return laneCalibrationCaptureThread;
}

/**
 * @brief Get the CalibrationPreviewCameraThread
 *
 * @return CalibrationPreviewCameraThread*
 */
CalibrationPreviewCameraThread *
ThreadController::getCalibrationPreviewCameraThread() {
    return calibrationPreviewCameraThread;
}

/**
 * @brief Get the CalibrationPreviewCaptureThread
 *
 * @return CalibrationPreviewCaptureThread*
 */
CalibrationPreviewCaptureThread *
ThreadController::getCalibrationPreviewCaptureThread() {
    return calibrationPreviewCaptureThread;
}

/**
 * @brief Get the LaneManualCalibrationCameraThread
 *
 * @return LaneManualCalibrationCameraThread*
 */
ManualCalibrationCameraThread *
ThreadController::getLaneManualCalibrationCameraThread() {
    return laneManualCalibrationCameraThread;
}

/**
 * @brief Get the LaneManualCalibrationCaptureThread
 *
 * @return LaneManualCalibrationCaptureThread*
 */
LaneManualCalibrationCaptureThread *
ThreadController::getLaneManualCalibrationCaptureThread() {
    return laneManualCalibrationCaptureThread;
}

/**
 * @brief Get the DistanceCalibrationCameraThread
 *
 * @return DistanceCalibrationCameraThread*
 */
DistanceCalibrationCameraThread *
ThreadController::getDistanceCalibrationCameraThread() {
    return distanceCalibrationCameraThread;
}

/**
 * @brief Get the DistanceCalibrationCaptureThread
 *
 * @return DistanceCalibrationCaptureThread*
 */
DistanceCalibrationCaptureThread *
ThreadController::getDistanceCalibrationCaptureThread() {
    return distanceCalibrationCaptureThread;
}

/**
 * @brief Get the ColorCalibrationThread
 *
 * @return ColorCalibrationThread*
 */
ColorCalibrationThread *ThreadController::getColorCalibrationThread() {
    return colorCalibrationThread;
}

/**
 * @brief Get the ColorCalibrationPreviewThread
 *
 * @return ColorCalibrationPreviewThread*
 */
ColorCalibrationPreviewThread *ThreadController::getColorCalibPreviewThread() {
    return colorCalibPreviewThread;
}

/**
 * @brief Get the RoiThread
 *
 * @return RoiThread*
 */
RoiThread *ThreadController::getRoiThread() { return roiThread; }

/**
 * @brief Get the RoiPreviewThread
 *
 * @return RoiPreviewThread*
 */
RoiPreviewThread *ThreadController::getRoiPreviewThread() {
    return roiPreviewThread;
}

/**
 * @brief Get the ProcessThread
 *
 * @return ProcessThread*
 */
ProcessThread *ThreadController::getProcessThread() { return processThread; }

/**
 * @brief Get the ResultPreviewThread
 *
 * @return ResultPreviewThread*
 */
ResultPreviewThread *ThreadController::getResultPreviewThread() {
    return resultPreviewThread;
}

/**
 * @brief Get the TrimDataThread
 *
 * @return TrimDataThread*
 */
TrimDataThread *ThreadController::getTrimDataThread() { return trimDataThread; }

/**
 * @brief Handle the start of the LoadFileThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param path Path to the file
 * @param panelID PanelID of the panel
 */
void ThreadController::startLoadFileHandler(wxEvtHandler *parent, DataPtr data,
                                            std::string path, PanelID panelID) {

    loadFileThread = new LoadFileThread(parent, data, path);
    loadFileThread->Run();

    owner[loadFileThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LoadFileThread
 *
 */
void ThreadController::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

/**
 * @brief Handle the start of the SaveFileThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startSaveFileHandler(wxEvtHandler *parent, DataPtr data,
                                            PanelID panelID) {

    saveFileThread = new SaveDataThread(parent, data);
    saveFileThread->Run();

    owner[saveFileThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the SaveFileThread
 *
 */
void ThreadController::endSaveFileHandler() {
    saveFileThread = stopAndDeleteThread(saveFileThread);
}

/**
 * @brief Handle the start of the LaneCalibrationCameraThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param camera Unique pointer to the Camera
 * @param hsvFilter Pointer to the HSVFilter
 * @param bfs Pointer to the BFS
 * @param ransac Pointer to the RansacLine
 * @param panelID PanelID of the panel
 */
void ThreadController::startLaneCalibrationCameraHandler(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera,
    HSVFilterPtr hsvFilter, BFSPtr bfs, RansacLinePtr ransac, PanelID panelID) {

    laneCalibrationCameraThread = new LaneCalibrationCameraThread(
        parent, data, camera, hsvFilter, bfs, ransac);
    laneCalibrationCameraThread->Run();

    owner[laneCalibrationCameraThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LaneCalibrationCameraThread
 *
 */
void ThreadController::endLaneCalibrationCameraHandler() {
    laneCalibrationCameraThread =
        stopAndDeleteThread(laneCalibrationCameraThread);
}

/**
 * @brief Handle the start of the LaneCalibrationCaptureThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param hsvFilter Pointer to the HSVFilter
 * @param bfs Pointer to the BFS
 * @param ransac Pointer to the RansacLine
 * @param panelID PanelID of the panel
 */
void ThreadController::startLaneCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, HSVFilterPtr hsvFilter, BFSPtr bfs,
    RansacLinePtr ransac, PanelID panelID) {

    laneCalibrationCaptureThread =
        new LaneCalibrationCaptureThread(parent, data, hsvFilter, bfs, ransac);
    laneCalibrationCaptureThread->Run();

    owner[laneCalibrationCaptureThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LaneCalibrationCaptureThread
 *
 */
void ThreadController::endLaneCalibrationCaptureHandler() {
    laneCalibrationCaptureThread =
        stopAndDeleteThread(laneCalibrationCaptureThread);
}

/**
 * @brief Handle the start of the CalibrationPreviewCameraThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startCalibrationPreviewCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, DataPtr data, PanelID panelID) {
    calibrationPreviewCameraThread =
        new CalibrationPreviewCameraThread(parent, data, camera);
    calibrationPreviewCameraThread->Run();

    owner[calibrationPreviewCameraThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the CalibrationPreviewCameraThread
 *
 */
void ThreadController::endCalibrationPreviewCameraHandler() {
    calibrationPreviewCameraThread =
        stopAndDeleteThread(calibrationPreviewCameraThread);
}

/**
 * @brief Handle the start of the CalibrationPreviewCaptureThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startCalibrationPreviewCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {
    calibrationPreviewCaptureThread =
        new CalibrationPreviewCaptureThread(parent, data);
    calibrationPreviewCaptureThread->Run();

    owner[calibrationPreviewCaptureThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the CalibrationPreviewCaptureThread
 *
 */
void ThreadController::endCalibrationPreviewCaptureHandler() {
    calibrationPreviewCaptureThread =
        stopAndDeleteThread(calibrationPreviewCaptureThread);
}

/**
 * @brief Handle the start of the LaneManualCalibrationCameraThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param panelID PanelID of the panel
 */
void ThreadController::startLaneManualCalibrationCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, PanelID panelID) {

    laneManualCalibrationCameraThread =
        new ManualCalibrationCameraThread(parent, camera);
    laneManualCalibrationCameraThread->Run();

    owner[laneManualCalibrationCameraThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LaneManualCalibrationCameraThread
 *
 */
void ThreadController::endLaneManualCalibrationCameraHandler() {
    laneManualCalibrationCameraThread =
        stopAndDeleteThread(laneManualCalibrationCameraThread);
}

/**
 * @brief Handle the start of the LaneManualCalibrationCaptureThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startManualCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    laneManualCalibrationCaptureThread =
        new LaneManualCalibrationCaptureThread(parent, data);
    laneManualCalibrationCaptureThread->Run();

    owner[laneManualCalibrationCaptureThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the LaneManualCalibrationCaptureThread
 *
 */
void ThreadController::endManualCalibrationCaptureHandler() {
    laneManualCalibrationCaptureThread =
        stopAndDeleteThread(laneManualCalibrationCaptureThread);
}

/**
 * @brief Handle the start of the DistanceCalibrationCameraThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param panelID PanelID of the panel
 */
void ThreadController::startDistaneCalibrationCameraHandler(
    wxEvtHandler *parent, CameraPtr &camera, PanelID panelID) {

    distanceCalibrationCameraThread =
        new DistanceCalibrationCameraThread(parent, camera);
    distanceCalibrationCameraThread->Run();

    owner[distanceCalibrationCameraThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the DistanceCalibrationCameraThread
 *
 */
void ThreadController::endDistanceCalibrationCameraHandler() {
    distanceCalibrationCameraThread =
        stopAndDeleteThread(distanceCalibrationCameraThread);
}

/**
 * @brief Handle the start of the DistanceCalibrationCaptureThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startDistanceCalibrationCaptureHandler(
    wxEvtHandler *parent, DataPtr data, PanelID panelID) {

    distanceCalibrationCaptureThread =
        new DistanceCalibrationCaptureThread(parent, data);
    distanceCalibrationCaptureThread->Run();

    owner[distanceCalibrationCaptureThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the DistanceCalibrationCaptureThread
 *
 */
void ThreadController::endDistanceCalibrationCaptureHandler() {
    distanceCalibrationCaptureThread =
        stopAndDeleteThread(distanceCalibrationCaptureThread);
}

/**
 * @brief Handle the start of the ColorCalibrationThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param camera Unique pointer to the Camera
 * @param hsvFilter Pointer to the HSVFilter
 * @param bfs Pointer to the BFS
 * @param panelID PanelID of the panel
 */
void ThreadController::startColorCalibrationHandler(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera,
    HSVFilterPtr hsvFilter, BFSPtr bfs, PanelID panelID) {

    colorCalibrationThread =
        new ColorCalibrationThread(parent, data, camera, hsvFilter, bfs);
    colorCalibrationThread->Run();

    owner[colorCalibrationThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the ColorCalibrationThread
 *
 */
void ThreadController::endColorCalibrationHandler() {
    colorCalibrationThread = stopAndDeleteThread(colorCalibrationThread);
}

/**
 * @brief Handle the start of the ColorCalibrationPreviewThread
 *
 * @param parent Pointer to the View
 * @param camera Unique pointer to the Camera
 * @param blueRange The blue color range
 * @param yellowRange The yellow color range
 * @param panelID PanelID of the panel
 */
void ThreadController::startColorCalibrationPreviewHandler(
    wxEvtHandler *parent, CameraPtr &camera, const ColorRange &blueRange,
    const ColorRange &yellowRange, PanelID panelID) {
    colorCalibPreviewThread = new ColorCalibrationPreviewThread(
        parent, camera, blueRange, yellowRange);
    colorCalibPreviewThread->Run();

    owner[colorCalibPreviewThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the ColorCalibrationPreviewThread
 *
 */
void ThreadController::endColorCalibrationPreviewHandler() {
    colorCalibPreviewThread = stopAndDeleteThread(colorCalibPreviewThread);
}

/**
 * @brief Handle the start of the RoiThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startRoiHandler(wxEvtHandler *parent, DataPtr data,
                                       PanelID panelID) {
    roiThread = new RoiThread(parent, data);
    roiThread->Run();

    owner[roiThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the RoiThread
 *
 */
void ThreadController::endRoiHandler() {
    roiThread = stopAndDeleteThread(roiThread);
}

/**
 * @brief Handle the start of the RoiPreviewThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startRoiPreviewHandler(wxEvtHandler *parent,
                                              DataPtr data, PanelID panelID) {
    roiPreviewThread = new RoiPreviewThread(parent, data);
    roiPreviewThread->Run();

    owner[roiPreviewThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the RoiPreviewThread
 *
 */
void ThreadController::endRoiPreviewHandler() {
    roiPreviewThread = stopAndDeleteThread(roiPreviewThread);
}

/**
 * @brief Handle the start of the ProcessThread
 *
 * @param parent Pointer to the View
 * @param threadPool Pointer to the ThreadPool
 * @param data Pointer to the SessionData
 * @param detector Pointer to the FeatureDetector
 * @param tracker Pointer to the Tracker
 * @param speedCalc Pointer to the SpeedCalculation
 * @param panelID PanelID of the panel
 */
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

/**
 * @brief Handle the end of the ProcessThread
 *
 */
void ThreadController::endProcessHandler() {
    processThread = stopAndDeleteThread(processThread);
}

/**
 * @brief Handle the start of the ResultPreviewThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startResultPreviewHandler(wxEvtHandler *parent,
                                                 DataPtr data,
                                                 PanelID panelID) {
    resultPreviewThread = new ResultPreviewThread(parent, data);
    resultPreviewThread->Run();

    owner[resultPreviewThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the ResultPreviewThread
 *
 */
void ThreadController::endResultPreviewHandler() {
    resultPreviewThread = stopAndDeleteThread(resultPreviewThread);
}

/**
 * @brief Handle the start of the TrimDataThread
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param panelID PanelID of the panel
 */
void ThreadController::startTrimDataHandler(wxEvtHandler *parent, DataPtr data,
                                            PanelID panelID) {
    trimDataThread = new TrimDataThread(parent, data);
    trimDataThread->Run();

    owner[trimDataThread->getID()] = panelID;
}

/**
 * @brief Handle the end of the TrimDataThread
 *
 */
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

/**
 * @brief Kill all threads
 *
 */
void ThreadController::killAllThreads() { deleteThread(); }
