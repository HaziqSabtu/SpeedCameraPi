#include "Event/Event_UpdateStatus.hpp"
#include "Thread/Thread_HorizontalCalibrationCamera.hpp"
#include "Thread/Thread_ID.hpp"
#include "UI/Data/StatusData.hpp"
#include "UI/Dialog/RemoveCalibrationDialog.hpp"
#include <Controller/HorizontalCalibrationController.hpp>

HorizontalCalibrationController::HorizontalCalibrationController(
    ModelPtr sharedModel)
    : BaseControllerWithTouch(sharedModel) {
    panelID = currentPanelID;
}

HorizontalCalibrationController::~HorizontalCalibrationController() {}

void HorizontalCalibrationController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("horizontalCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("horizontalCalibCapTureThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        throw std::runtime_error("calibCapPrevThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        throw std::runtime_error("calibPrevThread is running");
    }
}

void HorizontalCalibrationController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        horizontalCalibrationCameraEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        horizontalCalibrationCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        calibrationPreviewCaptureEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        calibrationPreviewCameraEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void HorizontalCalibrationController::e_ChangeToBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_ChangeToTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        changeToTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_HorizontalCalibrationCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        horizontalCalibrationCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewCameraStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewCameraEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCameraEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewCaptureStart(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_CalibrationPreviewCaptureEnd(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        calibrationPreviewCaptureEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_RemoveBottom(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeBottomHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_RemoveTop(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeTopHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::e_RemoveCalibrationData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        removeCalibrationDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void HorizontalCalibrationController::changeToBottomHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setDirection(HorizontalDirection::HORIZONTAL_BOTTOM);

    UpdateStatusEvent::Submit(parent, SC::STATUS_HORIZONTAL_SELECTBOTTOM);
}

void HorizontalCalibrationController::changeToTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setDirection(HorizontalDirection::HORIZONTAL_TOP);

    UpdateStatusEvent::Submit(parent, SC::STATUS_HORIZONTAL_SELECTTOP);
}

void HorizontalCalibrationController::leftDownHandler(wxEvtHandler *parent,
                                                      cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setPointAndExtend(point);
}

void HorizontalCalibrationController::leftMoveHandler(wxEvtHandler *parent,
                                                      cv::Point point) {
    // throw std::runtime_error("Blocked Endpoint");
    leftDownHandler(parent, point);
}

void HorizontalCalibrationController::leftUpHandler(wxEvtHandler *parent,
                                                    cv::Point point) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setPointAndExtend(point);

    auto dir = thread->getDirection();
    auto line = dir == HORIZONTAL_TOP ? thread->getRealTopLine()
                                      : thread->getRealBottomLine();

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    dir == HORIZONTAL_TOP ? calibData.lineRight = line
                          : calibData.lineLeft = line;

    data->setCalibrationData(calibData);
}

void HorizontalCalibrationController::horizontalCalibrationStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        horizontalCalibrationCameraStartHandler(parent);
    } else {
        horizontalCalibrationCaptureStartHandler(parent);
    }
}

void HorizontalCalibrationController::horizontalCalibrationEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("CalibrationThread is not running");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();
    if (thread->getID() == THREAD_HORIZONTAL_CALIBRATION_CAMERA) {
        horizontalCalibrationCameraEndHandler(parent);
    } else {
        horizontalCalibrationCaptureEndHandler(parent);
    }
}

void HorizontalCalibrationController::horizontalCalibrationCameraStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    auto camera = shared->getCamera();

    tc->startHorizontalCalibrationCameraHandler(parent, camera, panelID);
}

void HorizontalCalibrationController::horizontalCalibrationCameraEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAMERA)) {
        throw std::runtime_error("CalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_HORIZONTAL_CALIBRATION_CAMERA, panelID)) {
        throw std::runtime_error("CalibThread is not owned by this panel");
    }

    auto thread = tc->getHorizontalCalibrationCameraThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endHorizontalCalibrationCameraHandler();
}

void HorizontalCalibrationController::horizontalCalibrationCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    DataPtr data = shared->getSessionData();

    tc->startHorizontalCalibrationCaptureHandler(parent, data, panelID);
}

void HorizontalCalibrationController::horizontalCalibrationCaptureEndHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_HORIZONTAL_CALIBRATION_CAPTURE)) {
        throw std::runtime_error("CalibCaptureThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_HORIZONTAL_CALIBRATION_CAPTURE, panelID)) {
        throw std::runtime_error(
            "CalibCaptureThread is not owned by this panel");
    }

    auto thread = tc->getHorizontalCalibrationCaptureThread();
    thread->Pause();

    tc->endHorizontalCalibrationCaptureHandler();
}

void HorizontalCalibrationController::calibrationPreviewStartHandler(
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

void HorizontalCalibrationController::calibrationPreviewEndHandler(
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

void HorizontalCalibrationController::calibrationPreviewCameraStartHandler(
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

void HorizontalCalibrationController::calibrationPreviewCameraEndHandler(
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

void HorizontalCalibrationController::calibrationPreviewCaptureStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("capture data is empty");
    }

    tc->startCalibrationPreviewCaptureHandler(parent, data, panelID);
}

void HorizontalCalibrationController::calibrationPreviewCaptureEndHandler(
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

void HorizontalCalibrationController::removeBottomHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setBottomLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineLeft = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_HORIZONTAL_REMOVEBOTTOM);
}

void HorizontalCalibrationController::removeTopHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isHorizontalCalibrationThreadRunning()) {
        throw std::runtime_error("Calibration thread is not running");
    }

    if (!tc->isHorizontalCalibrationThreadOwner(panelID)) {
        throw std::runtime_error(
            "Calibration thread is not owned by this panel");
    }

    auto thread = tc->getRunningHorizontalCalibrationThread();

    thread->setTopLine(Line());

    auto data = shared->getSessionData();

    auto calibData = data->getCalibrationData();

    calibData.lineRight = Line();

    data->setCalibrationData(calibData);

    UpdateStatusEvent::Submit(parent, SC::STATUS_HORIZONTAL_REMOVETOP);
}

void HorizontalCalibrationController::removeCalibrationDataHandler(
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

void HorizontalCalibrationController::panelShowHandler(wxEvtHandler *parent) {
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

    horizontalCalibrationCameraStartHandler(parent);
}
