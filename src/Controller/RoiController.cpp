#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_UpdateState.hpp"
#include <Controller/RoiController.hpp>

#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include "Utils/wxUtils.hpp"
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/object.h>

RoiController::RoiController(ModelPtr sharedModel) : shared(sharedModel) {}

RoiController::~RoiController() {}

void RoiController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_ClearRect(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        clearRectHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_SetPoint1(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();

        setPoint1Handler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_SetPoint2(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();

        setPoint2Handler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RoiThreadStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiThreadStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RoiThreadEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "RoiController::endPoint() - PanelID mismatch");
    }
}

void RoiController::clearRectHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::clearRectHandler() - Thread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::clearRectHandler() - Thread is not owned by this "
            "controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint1(cv::Point(-1, -1));
    roiThread->setPoint2(cv::Point(-1, -1));
}

void RoiController::setPoint1Handler(wxEvtHandler *parent, cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::setPoint1Handler() - Thread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::setPoint1Handler() - Thread is not owned by this "
            "controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint1(point);
}

void RoiController::setPoint2Handler(wxEvtHandler *parent, cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::setPoint2Handler() - Thread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::setPoint2Handler() - Thread is not owned by this "
            "controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint2(point);
}

void RoiController::roiThreadStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::roiThreadStartHandler() - Thread is already "
            "running");
    }

    auto sessionData = shared->getSessionData();

    auto imageData = sessionData->imageData;

    tc->startRoiHandler(parent, imageData, panelID);
}

void RoiController::roiThreadEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::roiThreadEndHandler() - Thread is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::roiThreadEndHandler() - Thread is not owned by "
            "this controller");
    }

    tc->endRoiHandler();
}
