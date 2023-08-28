#include <Controller/CaptureController.hpp>

CaptureController::CaptureController(ModelPtr sharedModel)
    : BaseController(sharedModel) {
    panelID = currentPanelID;
}

CaptureController::~CaptureController() {}

void CaptureController::e_ChangeToCalibPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToCalibPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ChangeToRoiPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToRoiPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ChangeToResultPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToResultPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_SaveSessionDataStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_SaveSessionDataEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ResetSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        resetSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ChangeToTrimDataPanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToTrimDataPanelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ClearImageData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        clearImageDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_RemoveCalibration(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_RemoveRoi(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeRoiHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ReplayStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        replayStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_ReplayEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        replayEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_CameraStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        captureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_CameraEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        captureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadFileStart(wxEvtHandler *parent,
                                        std::string path) {
    try {
        checkPreCondition();
        loadFileStartHandler(parent, path);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadFileEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadFileEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadCaptureStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::e_LoadCaptureEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        loadCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CaptureController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        throw std::runtime_error("captureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        throw std::runtime_error("loadFileThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        throw std::runtime_error("loadCaptureThread is already running");
    }

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        throw std::runtime_error("replayThread is already running");
    }
}

void CaptureController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_CAPTURE)) {
        captureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_FILE)) {
        loadFileEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_LOAD_CAPTURE)) {
        loadCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_REPLAY)) {
        replayEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

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
}

void CaptureController::captureStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Error acquiring camera");
    }

    auto camera = shared->getCamera();
    tc->startCaptureHandler(parent, camera, panelID);
}

void CaptureController::captureEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CAPTURE)) {
        throw std::runtime_error("captureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CAPTURE, panelID)) {
        throw std::runtime_error("captureThread is not owned by this panel");
    }

    auto captureThread = tc->getCaptureThread();
    captureThread->Pause();

    auto camera = captureThread->getCamera();
    shared->setCamera(camera);

    tc->endCaptureHandler();
}

void CaptureController::loadFileStartHandler(wxEvtHandler *parent,
                                             std::string path) {

    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is not empty");
    }

    AppConfig config;
    auto c = config.GetLoadConfig();

    auto data = shared->getSessionData();

    tc->startLoadFileHandler(parent, data, c.maxFrame, path, panelID);
}

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

void CaptureController::loadCaptureStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

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

void CaptureController::replayStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (shared->sessionData.isCaptureDataEmpty()) {
        throw std::runtime_error("ImageData is Empty");
    }

    auto data = shared->getSessionData();

    tc->startReplayHandler(parent, data, panelID);
}

void CaptureController::replayEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_REPLAY)) {
        throw std::runtime_error("replayThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_REPLAY, panelID)) {
        throw std::runtime_error("replayThread is not owned by this panel");
    }

    tc->endReplayHandler();
}

void CaptureController::removeCalibrationHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isCalibrationDataEmpty()) {
        throw std::runtime_error("CalibrationData is empty");
    }

    shared->sessionData.removeCalibrationData();

    // TODO: Add this to StatusCollection
    wxString msg = "Calibration data is removed";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::removeRoiHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isCapturePanelThreadRunning()) {
        throw std::runtime_error("Thread of Capture Panel is running");
    }

    if (shared->sessionData.isTrackingDataEmpty()) {
        throw std::runtime_error("RoiData is empty");
    }

    shared->sessionData.clearTrackingData();

    // TODO: Add this to StatusCollection
    wxString msg = "Roi data is removed";
    UpdateStatusEvent::Submit(parent, msg);
}

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
        // TODO: Add this to StatusCollection
        wxString msg = "Save Cancelled";
        UpdateStatusEvent::Submit(parent, msg);
        return;
    }

    auto data = shared->getSessionData();

    tc->startSaveFileHandler(parent, data, panelID);
}

void CaptureController::saveSessionDataEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_SAVE_FILE)) {
        throw std::runtime_error("saveFileThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_SAVE_FILE, panelID)) {
        throw std::runtime_error("saveFileThread is not owned by this panel");
    }

    tc->endSaveFileHandler();

    // TODO: Add this to StatusCollection
    wxString msg = "Save Complete";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::resetSessionDataHandler(wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    auto dialog = new ResetDataDialog(nullptr);
    if (dialog->ShowModal() == wxID_NO) {
        wxString msg = "Session Reset Cancelled";
        UpdateStatusEvent::Submit(parent, msg);

        return;
    }

    shared->resetSessionData();

    // TODO: Add this to StatusCollection
    wxString msg = "Session Reset Complete";
    UpdateStatusEvent::Submit(parent, msg);
}

void CaptureController::changeToCalibPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_CALIBRATION);
    ChangePanelEvent::Submit(parent, data);
}

void CaptureController::changeToRoiPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_ROI);
    ChangePanelEvent::Submit(parent, data);
}

void CaptureController::changeToResultPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    ChangePanelData data(panelID, PanelID::PANEL_RESULT);
    ChangePanelEvent::Submit(parent, data);
}

void CaptureController::changeToTrimDataPanelHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    // ask for confirmation
    // TODO: dialog
    auto wx = wxTheApp->GetTopWindow();
    auto dialog = new ResetDataDialog(wx);
    if (dialog->ShowModal() == wxID_NO) {
        wxString msg = "Session Reset Cancelled";
        UpdateStatusEvent::Submit(parent, msg);

        return;
    }

    ChangePanelData data(panelID, PanelID::PANEL_TRIM_DATA);
    ChangePanelEvent::Submit(parent, data);
}