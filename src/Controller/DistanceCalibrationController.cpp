#include "Event/Event_UpdateStatus.hpp"
#include "Thread/Thread_DistanceCalibrationCamera.hpp"
#include "Thread/Thread_ID.hpp"
#include "UI/Data/StatusData.hpp"
#include "UI/Dialog/RemoveCalibrationDialog.hpp"
#include <Controller/DistanceCalibrationController.hpp>

DistanceCalibrationController::DistanceCalibrationController(
    ModelPtr sharedModel)
    : BaseControllerWithTouch(sharedModel) {
    panelID = currentPanelID;
}

DistanceCalibrationController::~DistanceCalibrationController() {}

void DistanceCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("distanceCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("distanceCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

void DistanceCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        distanceCalibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        distanceCalibrationCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibrationPreviewCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        calibrationPreviewCameraEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void DistanceCalibrationController::e_ChangeToBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_ChangeToTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_DistanceCalibrationCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        distanceCalibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_RemoveBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_RemoveTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::e_RemoveCalibrationData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void DistanceCalibrationController::changeToBottomHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setDirection(DistanceDirection::DISTANCE_BOTTOM);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTBOTTOM);
}

void DistanceCalibrationController::changeToTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setDirection(DistanceDirection::DISTANCE_TOP);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_SELECTTOP);
}

void DistanceCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setPointAndExtend(point);
}

void DistanceCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    // throw std::runtime_error("Blocked Endpoint");
    leftDownHandler(parent, point);
}

void DistanceCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                                  cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setPointAndExtend(point);

    auto dir = thread->getDirection();
    auto line = dir == DISTANCE_TOP ? thread->getRealTopLine()
                                    : thread->getRealBottomLine();

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    dir == DISTANCE_TOP ? calibData.lineRight = line
                        : calibData.lineLeft = line;

    data->setCalibrationData(calibData);
}

void DistanceCalibrationController::distanceCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        distanceCalibrationCameraStartHandler(parent);
    } else {
        distanceCalibrationCaptureStartHandler(parent);
    }
}

void DistanceCalibrationController::distanceCalibrationEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();
    if (thread->getID() == THREAD_DISTANCE_CALIBRATION_CAMERA) {
        distanceCalibrationCameraEndHandler(parent);
    } else {
        distanceCalibrationCaptureEndHandler(parent);
    }
}

void DistanceCalibrationController::distanceCalibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startDistaneCalibrationCameraHandler(parent, camera, panelID);
}

void DistanceCalibrationController::distanceCalibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAMERA)) {
        throw std::runtime_error("CalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error("CalibThread is not owned by this panel");
    }

    auto thread = tc->getDistanceCalibrationCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endDistanceCalibrationCameraHandler();
}

void DistanceCalibrationController::distanceCalibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startDistanceCalibrationCaptureHandler(parent, data, panelID);
}

void DistanceCalibrationController::distanceCalibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_DISTANCE_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_DISTANCE_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "CalibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getDistanceCalibrationCaptureThread();
    thread->Pause();

    tc->endDistanceCalibrationCaptureHandler();
}

void DistanceCalibrationController::calibrationPreviewStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        calibrationPreviewCameraStartHandler(parent);
    } else {
        calibrationPreviewCaptureStartHandler(parent);
    }
}

void DistanceCalibrationController::calibrationPreviewEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isCalibPreviewThreadRunning()) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    auto thread = tc->getRunningCalibPreviewThread();
    if (thread->getID() == THREAD_CALIBRATION_PREVIEW_CAMERA) {
        calibrationPreviewCameraEndHandler(parent);
    } else {
        calibrationPreviewCaptureEndHandler(parent);
    }
}

void DistanceCalibrationController::calibrationPreviewCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error("camera is nullptr");
    }

    DataPtr data = shared->getSessionData();

    tc->startCalibrationPreviewCameraHandler(parent, camera, data, panelID);
}

void DistanceCalibrationController::calibrationPreviewCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAMERA, panelID)) {
        throw std::runtime_error("calibPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationPreviewCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibrationPreviewCameraHandler();
}

void DistanceCalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

void DistanceCalibrationController::calibrationPreviewCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW_CAPTURE, panelID)) {
        throw std::runtime_error(
            "calibCapPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibrationPreviewCaptureThread();
    thread->Pause();

    tc->endCalibrationPreviewCaptureHandler();
}

void DistanceCalibrationController::removeBottomHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setBottomLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_REMOVEBOTTOM);
}

void DistanceCalibrationController::removeTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isDistanceCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isDistanceCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningDistanceCalibrationThread();

    thread->setTopLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_DISTANCE_REMOVETOP);
}

void DistanceCalibrationController::removeCalibrationDataHandler(
    wxEvtHandler *parent) {
    throwIfAnyThreadIsRunning();

    auto wx = wxTheApp->GetTopWindow();
    auto dialog = RemoveCalibrationDialog(wx);
    if (dialog.ShowModal() == wxID_NO) {
        return;
    }

    shared->sessionData.removeCalibrationData();

    UpdateStatusEvent::Submit(parent, SC::STATUS_REMOVE_CALIBRATION_OK);
}

void DistanceCalibrationController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);

    auto data = shared->getSessionData();

    if (!data->isCalibrationDataEmpty()) {
        return;
    }

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoManualCalibration;

    if (!startThread) {
        return;
    }

    distanceCalibrationCameraStartHandler(parent);
}
