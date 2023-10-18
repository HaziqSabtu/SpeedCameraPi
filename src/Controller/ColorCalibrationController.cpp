#include <Controller/ColorCalibrationController.hpp>

ColorCalibrationController::ColorCalibrationController(ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

ColorCalibrationController::~ColorCalibrationController() {}

void ColorCalibrationController::e_RestoreRange(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        restoreRangeHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SetTypeBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setTypeBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SetTypeYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setTypeYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ColorCalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_RemoveBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_RemoveYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SaveBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SaveYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SaveColorCalibration(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveColorCalibrationHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("ColorCalibrationPreviewThread is running");
    }
}

void ColorCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        colorCalibrationEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        colorCalibrationPreviewEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void ColorCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                 cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->setPoint(point);
}

void ColorCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                 cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void ColorCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                               cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

void ColorCalibrationController::restoreRangeHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    // TODO: Add dialog to confirm

    auto config = AppConfig();
    config.ResetBlueRange();
    config.ResetYellowRange();

    UpdateStatusEvent::Submit(parent, "Range restored");
}

void ColorCalibrationController::setTypeBlueHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->setColorCalibrationType(COLOR_CALIBRATION_BLUE);
}

void ColorCalibrationController::setTypeYellowHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->setColorCalibrationType(COLOR_CALIBRATION_YELLOW);
}

void ColorCalibrationController::colorCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is already running");
    }

    auto camera = shared->getCamera();
    auto data = shared->getSessionData();

    AppConfig c;
    auto hsvFilter = AF::createHSVFilter(c);
    auto bfs = AF::createBFS(c);

    tc->startColorCalibrationHandler(parent, data, camera, hsvFilter, bfs,
                                     panelID);
}

void ColorCalibrationController::colorCalibrationEndHandler(
    wxEvtHandler *parent) {

    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    saveColorCalibrationHandler(parent);

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->Pause();

    auto camera = calibrationThread->getCamera();
    shared->setCamera(camera);

    tc->endColorCalibrationHandler();
}

void ColorCalibrationController::colorCalibrationPreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        throw std::runtime_error(
            "ColorCalibrationPreviewThread is already running");
    }

    auto camera = shared->getCamera();

    AppConfig c;
    auto blueRange = Utils::HSVRangeConfigToScalar(c.GetBlueRange());
    auto yellowRange = Utils::HSVRangeConfigToScalar(c.GetYellowRange());

    tc->startColorCalibrationPreviewHandler(parent, camera, blueRange,
                                            yellowRange, panelID);
}

void ColorCalibrationController::colorCalibrationPreviewEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        throw std::runtime_error(
            "ColorCalibrationPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationPreviewThread is not owned by this panel");
    }

    auto colorCalibPreviewThread = tc->getColorCalibPreviewThread();
    colorCalibPreviewThread->Pause();

    auto camera = colorCalibPreviewThread->getCamera();
    shared->setCamera(camera);

    tc->endColorCalibrationPreviewHandler();
}

void ColorCalibrationController::removeBlueHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->removeBlueRange();
}

void ColorCalibrationController::removeYellowHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->removeYellowRange();
}

void ColorCalibrationController::saveBlueHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto thread = tc->getColorCalibrationThread();

    auto blueRange = thread->getBlueRange();
    if (!Utils::isRangeCalibrated(blueRange)) {
        return;
    }

    AppConfig c;
    c.SetBlueRange(Utils::ScalarToHSVRangeConfig(blueRange));

    thread->setPoint(cv::Point(-1, -1));

    UpdateStatusEvent::Submit(parent, "Blue range saved");
}

void ColorCalibrationController::saveYellowHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is NOT running");
    }

    if (!tc->isThreadOwner(THREAD_COLOR_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ColorCalibrationThread is not owned by this panel");
    }

    auto thread = tc->getColorCalibrationThread();

    auto yellowRange = thread->getYellowRange();
    if (!Utils::isRangeCalibrated(yellowRange)) {
        return;
    }
    thread->setPoint(cv::Point(-1, -1));
    AppConfig c;
    c.SetYellowRange(Utils::ScalarToHSVRangeConfig(yellowRange));

    UpdateStatusEvent::Submit(parent, "Yellow range saved");
}

void ColorCalibrationController::saveColorCalibrationHandler(
    wxEvtHandler *parent) {

    saveBlueHandler(parent);
    saveYellowHandler(parent);

    UpdateStatusEvent::Submit(parent, "Color calibration saved");
}

void ColorCalibrationController::okButtonHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();
    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        saveColorCalibrationHandler(parent);
    }
    BaseController::okButtonHandler(parent);
}