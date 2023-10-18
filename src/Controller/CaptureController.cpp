#include <Controller/CaptureController.hpp>

#include <UI/Dialog/RemoveCalibrationDialog.hpp>
#include <UI/Dialog/RemoveRoiDialog.hpp>
#include <UI/Dialog/ResetDataDialog.hpp>
#include <UI/Dialog/SaveDataDialog.hpp>
#include <UI/Dialog/SwitchModeDialog.hpp>
#include <UI/Dialog/TrimDataDialog.hpp>

/**
 * @brief Construct a new Capture Controller:: Capture Controller object
 *
 * @param shared The Shared pointer to SharedResource
 */
CaptureController::CaptureController(ResourcePtr shared)
    : BaseController(shared) {
    panelID = currentPanelID;
}

/**
 * @brief Destroy the Capture Controller:: Capture Controller object
 *
 */
CaptureController::~CaptureController() {}

/**
 * @brief Endpoint to change to LaneCalibrationPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ChangeToLaneCalibrationPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToLaneCalibrationPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to change to RoiPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ChangeToRoiPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToRoiPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to change to ResultPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ChangeToResultPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToResultPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Change to DistanceCalibrationPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ChangeToDistanceCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToDistanceCalibrationPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start save SessionData to create binary file. (Initialize
 * process)
 * @note This method is different from BaseController::e_SaveSessionData()
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_SaveSessionDataStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to when save SessionData is finished. (Kill process)
 * @note This method is different from BaseController::e_SaveSessionData()
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_SaveSessionDataEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to reset SessionData.
 * @details ALL data will be removed. CaptureData, CalibrationData, TrackingData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ResetSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resetSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to change to TrimDataPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ChangeToTrimDataPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToTrimDataPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove captured data
 * @note This method is different from CaptureController::e_ResetSessionData().
 * In this method only CaptureData and TrackingData are removed, while
 * CalibrationData is remained. Use case -> when use in Tripod Stand, user does
 * not have to repeat the same calibration process.
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_ClearImageData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        clearImageDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove CalibrationData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_RemoveCalibration(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove TrackingData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::e_RemoveRoi(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeRoiHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start Capture Preview (CapturePreviewThread)
 *
 * @param parent
 */
void CaptureController::e_CapturePreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        capturePreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end Capture Preview (CapturePreviewThread)
 *
 * @param parent
 */
void CaptureController::e_CapturePreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        capturePreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start Camera Preview (CameraPreviewThread)
 *
 * @param parent
 */
void CaptureController::e_CameraPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cameraPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end Camera Preview (CameraPreviewThread)
 *
 * @param parent
 */
void CaptureController::e_CameraPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cameraPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start Load File (LoadFileThread)
 *
 * @param parent
 * @param path
 */
void CaptureController::e_LoadFileStart(wxEvtHandler *parent,
                                        std::string path) {
    try {
        checkPreCondition();
        loadFileStartHandler(parent, path);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end Load File (LoadFileThread)
 *
 * @param parent
 */
void CaptureController::e_LoadFileEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadFileEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start Load Capture (LoadCaptureThread)
 *
 * @param parent
 */
void CaptureController::e_LoadCaptureStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end Load Capture (LoadCaptureThread)
 *
 * @param parent
 */
void CaptureController::e_LoadCaptureEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to toggle mode between Lane and Distance Calibration
 *
 * @param parent
 */
void CaptureController::e_ToggleMode(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        toggleModeHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Check if any thread is running, if yes, throw an exception
 *
 */
void CaptureController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        throw std::runtime_error("captureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("loadFileThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("loadCaptureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        throw std::runtime_error("replayThread is already running");
    }
}

/**
 * @brief Kill all threads by ThreadController. Used when navigating between
 * panels
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        cameraPreviewEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        loadFileEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        loadCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        capturePreviewEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

/**
 * @brief Handle the process of clearing CaptureData, TrackingData, ResultData
 * in SessionData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::clearImageDataHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is empty");
    }

    shared->sessionData.removeCaptureData();
    shared->sessionData.clearTrackingData();
    shared->sessionData.clearResultData();

    UpdateStatusEvent::Submit(parent, StatusCollection::STATUS_REMOVE_DATA);
    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    cameraPreviewStartHandler(parent);
}

/**
 * @brief Handle the process of initiating CameraPreviewThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::cameraPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    auto camera = shared->getCamera();
    tc->startCameraPreviewHandler(parent, camera, panelID);
}

/**
 * @brief Handle the process of ending CameraPreviewThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::cameraPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CAMERA_PREVIEW)) {
        throw std::runtime_error("captureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CAMERA_PREVIEW, panelID)) {
        throw std::runtime_error("captureThread is not owned by this panel");
    }

    auto captureThread = tc->getCameraPreviewThread();
    captureThread->Pause();

    auto camera = captureThread->getCamera();
    shared->setCamera(camera);

    tc->endCameraPreviewHandler();
}

/**
 * @brief Handle the process of initiating LoadFileThread
 *
 * @param parent the parent wxEvtHandler
 * @param path the path to the file
 */
void CaptureController::loadFileStartHandler(wxEvtHandler *parent,
                                             std::string path) {

    auto tc = shared->getThreadController();

    killAllThreads(parent);

    if (!shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    auto data = shared->getSessionData();

    tc->startLoadFileHandler(parent, data, path, panelID);
}

/**
 * @brief Handle the process of ending LoadFileThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::loadFileEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("loadFileThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LOAD_FILE, panelID)) {
        throw std::runtime_error("loadFileThread is not owned by this panel");
    }

    auto loadCaptureThread = tc->getLoadFileThread();

    tc->endLoadFileHandler();
}

/**
 * @brief Handle the process of initiating LoadCaptureThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::loadCaptureStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    killAllThreads(parent);
    // throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    if (!shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto captureConfig = config.GetCaptureConfig();
    int maxFrame = captureConfig.maxFrame;
    bool debug_ShowImage = captureConfig.DebugShowImage;
    bool debug_Save = captureConfig.DebugSave;

    auto camera = shared->getCamera();
    auto data = shared->getSessionData();

    tc->startLoadCaptureHandler(parent, camera, data, maxFrame, debug_ShowImage,
                                debug_Save, panelID);
}

/**
 * @brief Handle the process of ending LoadCaptureThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::loadCaptureEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("loadCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_LOAD_CAPTURE, panelID)) {
        throw std::runtime_error(
            "loadCaptureThread is not owned by this panel");
    }

    auto loadCaptureThread = tc->getLoadCaptureThread();

    auto camera = loadCaptureThread->getCamera();
    shared->setCamera(camera);

    tc->endLoadCaptureHandler();

    UpdateStatusEvent::Submit(parent, StatusCollection::STATUS_CAPTURE_END);
}

/**
 * @brief Handle the process of initiating CapturePreviewThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::capturePreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is Empty");
    }

    auto data = shared->getSessionData();

    tc->startCapturePreviewHandler(parent, data, panelID);
}

/**
 * @brief Handle the process of ending CapturePreviewThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::capturePreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CAPTURE_PREVIEW)) {
        throw std::runtime_error("replayThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CAPTURE_PREVIEW, panelID)) {
        throw std::runtime_error("replayThread is not owned by this panel");
    }

    tc->endCapturePreviewHandler();
}

/**
 * @brief Handle the process of removing CalibrationData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::removeCalibrationHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isCalibrationDataEmpty()) {
        throw std::runtime_error("CalibrationData is empty");
    }

#if DEBUG
#else
    auto wx = wxTheApp->GetTopWindow();
    auto dialog = new RemoveCalibrationDialog(wx);
    if (dialog->ShowModal() == wxID_NO) {
        return;
    }
#endif

    shared->sessionData.removeCalibrationData();
    UpdateStatusEvent::Submit(parent, SC::STATUS_REMOVE_CALIBRATION_OK);
}

/**
 * @brief Handle the process of removing TrackingData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::removeRoiHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isTrackingDataEmpty()) {
        throw std::runtime_error("RoiData is empty");
    }

#if DEBUG
#else
    auto wx = wxTheApp->GetTopWindow();
    auto dialog = new RemoveRoiDialog(wx);
    if (dialog->ShowModal() == wxID_NO) {
        return;
    }
#endif

    shared->sessionData.clearTrackingData();
    UpdateStatusEvent::Submit(parent, SC::STATUS_REMOVE_ROI_OK);
}

/**
 * @brief Handle the process of initiating SaveFileThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::saveSessionDataStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("Capture Data is empty");
    }

    auto id = shared->getSessionData()->getID();
    auto filename = Utils::idToFileName(id);

    auto dialog = new SaveDataDialog(nullptr, filename);
    if (dialog->ShowModal() == wxID_NO) {
        UpdateStatusEvent::Submit(parent, SC::STATUS_SAVE_DATA_CANCEL);
        return;
    }

    auto data = shared->getSessionData();

    tc->startSaveFileHandler(parent, data, panelID);
}

/**
 * @brief Handle the process of ending SaveFileThread
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::saveSessionDataEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_SAVE_FILE)) {
        throw std::runtime_error("saveFileThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_SAVE_FILE, panelID)) {
        throw std::runtime_error("saveFileThread is not owned by this panel");
    }

    tc->endSaveFileHandler();
}

/**
 * @brief Handle the process of resetting SessionData
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::resetSessionDataHandler(wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    auto dialog = new ResetDataDialog(nullptr);
    if (dialog->ShowModal() == wxID_NO) {
        UpdateStatusEvent::Submit(parent, SC::STATUS_RESET_SESSION_CANCEL);
        return;
    }

    shared->resetSessionData();

    UpdateStatusEvent::Submit(parent, SC::STATUS_RESET_SESSION_OK);
}

/**
 * @brief Handle the process of changing to LaneCalibrationPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::changeToLaneCalibrationPanelHandler(
    wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_LANE_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Handle the process of changing to RoiPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::changeToRoiPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_ROI);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Handle the process of changing to ResultPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::changeToResultPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_RESULT);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Handle the process of changing to TrimDataPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::changeToTrimDataPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    auto wx = wxTheApp->GetTopWindow();
    auto dialog = new TrimDataDialog(wx);

    if (dialog->ShowModal() == wxID_NO) {
        return;
    }

    auto data = shared->getSessionData();
    data->removeCalibrationData();
    data->clearTrackingData();
    shared->setSessionData(*data);

    ChangePanelData changeToTrimPanelEvent(panelID, PanelID::PANEL_TRIM_DATA);
    ChangePanelEvent::Submit(parent, changeToTrimPanelEvent);
}

/**
 * @brief Handle the process of changing to DistanceCalibrationPanel
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::changeToDistanceCalibrationPanelHandler(
    wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_DISTANCE_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Override method from BaseController. With this panel, we do not need
 * to create TempSessionData
 *
 */
void CaptureController::panelShowHandler(wxEvtHandler *parent) {
    // do nothing
    // do not create temp session data

    if (shared->sessionData.isCaptureDataEmpty()) {
        cameraPreviewStartHandler(parent);
    }
}

/**
 * @brief Override method from BaseController. Disable ok Button
 *
 */
void CaptureController::okButtonHandler(wxEvtHandler *parent) {
    throw std::runtime_error("Blocked Endpoint");
}

/**
 * @brief Override method from BaseController. Disable cancel Button
 *
 */
void CaptureController::cancelButtonHandler(wxEvtHandler *parent) {
    throw std::runtime_error("Blocked Endpoint");
}

/**
 * @brief Handle the process of toggling mode between Lane and Distance
 * Calibration
 *
 * @param parent the parent wxEvtHandler
 */
void CaptureController::toggleModeHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        return;
    }

    if (!shared->sessionData.isCalibrationDataEmpty()) {
        auto wx = wxTheApp->GetTopWindow();
        auto dialog = new SwitchModeDialog(wx);
        if (dialog->ShowModal() == wxID_NO) {
            wxCommandEvent cancelSwitchModeEvent(c_SWITCH_MODE_EVENT,
                                                 SWITCH_MODE_CANCEL);
            wxPostEvent(parent, cancelSwitchModeEvent);
            return;
        }

        removeCalibrationHandler(parent);
    }

    auto data = shared->getSessionData();
    data->toggleMode();

    wxCommandEvent okSwitchModeEvent(c_SWITCH_MODE_EVENT, SWITCH_MODE_OK);
    wxPostEvent(parent, okSwitchModeEvent);
}