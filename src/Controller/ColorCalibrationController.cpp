#include <Controller/ColorCalibrationController.hpp>

/**
 * @brief Construct a new Color Calibration Controller:: Color Calibration
 * Controller object
 *
 * @param shared Shared pointer to SharedResource
 */
ColorCalibrationController::ColorCalibrationController(ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

/**
 * @brief Destroy the Color Calibration Controller:: Color Calibration
 * Controller object
 *
 */
ColorCalibrationController::~ColorCalibrationController() {}

/**
 * @brief Endpoint to restoring hsv range to default value
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_RestoreRange(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        restoreRangeHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to set color calibration type to blue
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_SetTypeBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setTypeBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to set color calibration type to yellow
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_SetTypeYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        setTypeYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start color calibration (ColorCalibrationThread)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_ColorCalibrationStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end color calibration (ColorCalibrationThread)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_ColorCalibrationEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to start color calibration preview
 * (ColorCalibrationPreviewThread)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_ColorCalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to end color calibration preview
 * (ColorCalibrationPreviewThread)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_ColorCalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        colorCalibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove calibrated blue range
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_RemoveBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to remove calibrated yellow range
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_RemoveYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to save calibrated blue range
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_SaveBlue(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveBlueHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to save calibrated yellow range
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_SaveYellow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveYellowHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to save all calibrated range (blue and yellow)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::e_SaveColorCalibration(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveColorCalibrationHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Throw exception if any thread is running
 *
 */
void ColorCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("ColorCalibrationPreviewThread is running");
    }
}

/**
 * @brief Kill all running threads
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Left down handler
 * @details when left down, send point to ColorCalibrationThread to perform hsv
 * filtering
 *
 * @param parent Parent wxEvtHandler
 * @param point Point of mouse cursor
 */
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

/**
 * @brief Blocked endpoint. To only allow left down event
 *
 * @param parent
 * @param point
 */
void ColorCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                 cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

/**
 * @brief Blocked endpoint. To only allow left down event
 *
 * @param parent
 * @param point
 */
void ColorCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                               cv::Point point) {
    throw std::runtime_error("Blocked Endpoint");
}

/**
 * @brief Restore hsv range to default value
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Set color calibration type to blue
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Set color calibration type to yellow
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Start color calibration (ColorCalibrationThread)
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief End color calibration (ColorCalibrationThread)
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Start color calibration preview (ColorCalibrationPreviewThread)
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief End color calibration preview (ColorCalibrationPreviewThread)
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Remove calibrated blue range
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Remove calibrated yellow range
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Save calibrated blue range
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Save calibrated yellow range
 *
 * @param parent Parent wxEvtHandler
 */
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

/**
 * @brief Save all calibrated range (blue and yellow)
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::saveColorCalibrationHandler(
    wxEvtHandler *parent) {

    saveBlueHandler(parent);
    saveYellowHandler(parent);

    UpdateStatusEvent::Submit(parent, "Color calibration saved");
}

/**
 * @brief Override BaseController::okButtonHandler
 * @details Save all calibrated range (blue and yellow) before closing
 *
 * @param parent Parent wxEvtHandler
 */
void ColorCalibrationController::okButtonHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();
    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        saveColorCalibrationHandler(parent);
    }
    BaseController::okButtonHandler(parent);
}