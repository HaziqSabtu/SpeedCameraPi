#include "Event/Event_UpdateState.hpp"
#include "Model/AppState.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Model/SharedModel.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_ManualCalib.hpp"
#include "Utils/Struct/D_Line.hpp"
#include "Utils/wxUtils.hpp"

#include <Controller/ManualCalibrationController.hpp>

ManualCalibrationController::ManualCalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

void ManualCalibrationController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

ManualCalibrationController::~ManualCalibrationController() {}

void ManualCalibrationController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "ManualCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ManualCalibrationController::e_CreateTempSessionData(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();

        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        changeToLeftHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        changeToRightHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SetPoint1(wxEvtHandler *parent,
                                              wxPoint point) {
    try {
        checkPreCondition();

        setPoint1Handler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SetPoint2(wxEvtHandler *parent,
                                              wxPoint point) {
    try {
        checkPreCondition();

        setPoint2Handler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_SaveLine(wxEvtHandler *parent,
                                             wxPoint point) {
    try {
        checkPreCondition();

        saveLineHandler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ManualCalibEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        manualCalibEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibPrevStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibPrevStartHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_CalibPrevEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        calibPrevEndHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveLeft(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeLeftHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveRight(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeRightHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_RemoveCalibData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeCalibDataHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::changeToLeftHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::changeToLeftHandler() - "
            "THREAD_MANUAL_CALIBRATION is nullptr");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ManualCalibrationController::changeToLeftHandler() - "
            "THREAD_MANUAL_CALIBRATION is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setDirection(ManualDirection::MANUAL_LEFT);
}

void ManualCalibrationController::changeToRightHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::changeToLeftHandler() - "
            "THREAD_MANUAL_CALIBRATION is nullptr");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ManualCalibrationController::changeToLeftHandler() - "
            "THREAD_MANUAL_CALIBRATION is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setDirection(ManualDirection::MANUAL_RIGHT);
}

void ManualCalibrationController::setPoint1Handler(wxEvtHandler *parent,
                                                   cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint1Handler() - "
            "THREAD_MANUAL_CALIBRATION is nullptr");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint1Handler() - "
            "THREAD_MANUAL_CALIBRATION is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setPoint1(point);
}

void ManualCalibrationController::setPoint2Handler(wxEvtHandler *parent,
                                                   cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint2Handler() - "
            "THREAD_MANUAL_CALIBRATION is nullptr");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint2Handler() - "
            "THREAD_MANUAL_CALIBRATION is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setPoint2(point);
}

void ManualCalibrationController::saveLineHandler(wxEvtHandler *parent,
                                                  cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint2Handler() - "
            "THREAD_MANUAL_CALIBRATION is nullptr");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "ManualCalibrationController::setPoint2Handler() - "
            "THREAD_MANUAL_CALIBRATION is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setPoint2(point);

    auto dir = thread->getDirection();
    auto line =
        dir == MANUAL_LEFT ? thread->getBlueLine() : thread->getYellowLine();

    auto data = shared->getSessionData();

    auto commonData = data->getCommonData();

    auto config = AppConfig();
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    cv::Size src(pWidth, pHeight);

    auto cameraConfig = config.GetCameraConfig();

    int width = cameraConfig.Camera_Width;
    int height = cameraConfig.Camera_Height;
    cv::Size dst(width, height);

    auto realLine = line.Scale(src, dst);

    auto calibData = data->getCalibData();

    dir == MANUAL_LEFT ? calibData.lineLeft = realLine
                       : calibData.lineRight = realLine;

    data->setCalibData(calibData);
}

void ManualCalibrationController::manualCalibStartHandler(
    wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error(
            "ManualCalibrationController::manualCalibStartHandler() - "
            "THREAD_MANUAL_CALIBRATION is  not nullptr");
    }

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error(
            "ManualCalibrationController::manualCalibStartHandler() - "
            "camera is nullptr");
    }

    tc->startManualCalibrationHandler(parent, camera, panelID);
}

void ManualCalibrationController::manualCalibEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endManualCalibrationHandler();
}

void ManualCalibrationController::calibPrevStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibPrevThread is running");
    }

    auto camera = shared->getCamera();

    if (camera == nullptr) {
        throw std::runtime_error("camera is nullptr");
    }

    DataPtr data = shared->getSessionData();

    tc->startCalibPreviewHandler(parent, camera, data, panelID);
}

void ManualCalibrationController::calibPrevEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibPrevThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_CALIBRATION_PREVIEW, panelID)) {
        throw std::runtime_error("calibPrevThread is not owned by this panel");
    }

    auto thread = tc->getCalibPreviewThread();
    thread->Pause();

    auto camera = thread->getCamera();
    shared->setCamera(camera);

    tc->endCalibPreviewHandler();
}

void ManualCalibrationController::removeLeftHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setBlueLine(Detection::Line());
}

void ManualCalibrationController::removeRightHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_MANUAL_CALIBRATION, panelID)) {
        throw std::runtime_error(
            "manualCalibThread is not owned by this panel");
    }

    auto thread = tc->getManualCalibrationThread();
    thread->setYellowLine(Detection::Line());
}

void ManualCalibrationController::createTempSessionDataHandler(
    wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    if (!temp->isNull()) {
        throw std::runtime_error("TempSessionData is not null");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

void ManualCalibrationController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    //  will it ever null?
    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

void ManualCalibrationController::restoreSessionDataHandler(
    wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

void ManualCalibrationController::removeCalibDataHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_MANUAL_CALIBRATION)) {
        throw std::runtime_error("manualCalibThread is running");
    }

    if (!tc->isThreadNullptr(THREAD_CALIBRATION_PREVIEW)) {
        throw std::runtime_error("calibPreviewThread is running");
    }

    auto data = shared->getSessionData();

    data->removeCalibData();
}
