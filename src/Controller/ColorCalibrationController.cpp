#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/AppState.hpp"
#include "Model/SharedModel.hpp"
#include "Thread/Thread_ID.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/wxUtils.hpp"
#include <Controller/ColorCalibrationController.hpp>
#include <opencv2/core/types.hpp>

ColorCalibrationController::ColorCalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

ColorCalibrationController::~ColorCalibrationController() {}

void ColorCalibrationController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "ColorCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ColorCalibrationController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ChangeToCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SetPoint(wxEvtHandler *parent,
                                            wxPoint point) {
    try {
        checkPreCondition();

        setPointHandler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_SaveToConfig(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        saveToConfigHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_RestoreRange(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        restoreRangeHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_RemoveCalibratedRange(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeCalibratedRangeHandler(parent);
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

void ColorCalibrationController::setPointHandler(wxEvtHandler *parent,
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

void ColorCalibrationController::saveToConfigHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    auto ccExtraModel = shared->getCCExtraModel();

    auto blueRange = ccExtraModel->getBlueRange();
    if (!isRangeCalibrated(blueRange)) {
        throw std::runtime_error("Blue range is not calibrated");
    }

    auto yellowRange = ccExtraModel->getYellowRange();
    if (!isRangeCalibrated(yellowRange)) {
        throw std::runtime_error("Yellow range is not calibrated");
    }

    auto config = AppConfig();
    config.SetBlueRange(blueRange);
    config.SetYellowRange(yellowRange);

    UpdateStatusEvent::Submit(parent, "Saved to config");
}

void ColorCalibrationController::restoreRangeHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    auto config = AppConfig();
    config.ResetBlueRange();
    config.ResetYellowRange();

    UpdateStatusEvent::Submit(parent, "Range restored");
}

void ColorCalibrationController::removeCalibratedRangeHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is running");
    }

    auto ccExtraModel = shared->getCCExtraModel();

    ccExtraModel->resetBlueRange();
    ccExtraModel->resetYellowRange();

    UpdateStatusEvent::Submit(parent, "Range removed");
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

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION)) {
        throw std::runtime_error("ColorCalibrationThread is already running");
    }

    auto camera = shared->getCamera();

    tc->startColorCalibrationHandler(parent, camera, panelID);
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

    auto calibrationThread = tc->getColorCalibrationThread();
    calibrationThread->Pause();

    auto camera = calibrationThread->getCamera();
    shared->setCamera(camera);

    tc->endColorCalibrationHandler();
}

void ColorCalibrationController::colorCalibrationPreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (!tc->isThreadsWithCameraNullptr()) {
        throw std::runtime_error("Thread with camera is already running");
    }

    if (!tc->isThreadNullptr(THREAD_COLOR_CALIBRATION_PREVIEW)) {
        throw std::runtime_error(
            "ColorCalibrationPreviewThread is already running");
    }

    auto camera = shared->getCamera();

    auto ccExtraModel = shared->getCCExtraModel();

    tc->startColorCalibPreviewHandler(parent, camera, ccExtraModel, panelID);
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

    tc->endColorCalibPreviewHandler();
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

    auto colorCalibrationThread = tc->getColorCalibrationThread();

    auto blueRange = colorCalibrationThread->getBlueRange();
    if (!isRangeCalibrated(blueRange)) {
        throw std::runtime_error("Blue range is not calibrated");
    }
    auto ccModel = shared->getCCExtraModel();
    ccModel->setBlueRange(blueRange);

    colorCalibrationThread->setPoint(cv::Point(-1, -1));

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

    auto colorCalibrationThread = tc->getColorCalibrationThread();

    auto yellowRange = colorCalibrationThread->getYellowRange();
    if (!isRangeCalibrated(yellowRange)) {
        throw std::runtime_error("Yellow range is not calibrated");
    }
    auto ccModel = shared->getCCExtraModel();
    ccModel->setYellowRange(yellowRange);

    colorCalibrationThread->setPoint(cv::Point(-1, -1));

    UpdateStatusEvent::Submit(parent, "Yellow range saved");
}

void ColorCalibrationController::saveColorCalibrationHandler(
    wxEvtHandler *parent) {
    throw std::runtime_error("Not implemented");
}

bool ColorCalibrationController::isRangeCalibrated(
    const std::pair<cv::Scalar, cv::Scalar> &range) {
    return range.first != cv::Scalar(0, 0, 0) &&
           range.second != cv::Scalar(0, 0, 0);
}