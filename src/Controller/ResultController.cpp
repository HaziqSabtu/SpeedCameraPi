#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Event/Event_UpdateState.hpp"
#include <Controller/ResultController.hpp>

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

ResultController::ResultController(ModelPtr sharedModel)
    : shared(sharedModel) {}

ResultController::~ResultController() {}

void ResultController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessThreadStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        processThreadStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ProcessThreadEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        processThreadEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ResultPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        resultPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ResultPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        resultPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "ResultController::endPoint() - PanelID mismatch");
    }
}

void ResultController::processThreadStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_PROCESS)) {
        throw std::runtime_error(
            "ResultController::processThreadStartHandler() - Thread is already "
            "running");
    }

    auto sessionData = shared->getSessionData();

    auto imageData = sessionData->imageData;

    auto pool = shared->getThreadPool();

    tc->startProcessHandler(parent, pool, sessionData, panelID);
}

void ResultController::processThreadEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_PROCESS)) {
        throw std::runtime_error(
            "ResultController::processThreadEndHandler() - Thread is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_PROCESS, panelID)) {
        throw std::runtime_error("ResultController::processThreadEndHandler() "
                                 "- Thread is not owned by "
                                 "this controller");
    }

    tc->endProcessHandler();
}

void ResultController::resultPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error(
            "ResultController::resultPreviewStartHandler() - Thread is already "
            "running");
    }

    auto sessionData = shared->getSessionData();

    auto imageData = sessionData->imageData;

    auto pool = shared->getThreadPool();

    tc->startResultPreviewHandler(parent, sessionData, panelID);
}

void ResultController::resultPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error(
            "ResultController::resultPreviewEndHandler() - Thread is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error("ResultController::resultPreviewEndHandler() "
                                 "- Thread is not owned by "
                                 "this controller");
    }

    tc->endResultPreviewHandler();
}
