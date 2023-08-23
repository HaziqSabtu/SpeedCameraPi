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
#include "Thread/Thread_ResultPreview.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
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

void ResultController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        cancelButtonHandler(parent);
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

void ResultController::e_ToggleShowBox(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();

        toggleShowBoxHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ToggleShowLines(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();

        toggleShowLinesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_ToggleShowLanes(wxEvtHandler *parent, bool show) {
    try {
        checkPreCondition();

        toggleShowLanesHandler(parent, show);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::e_SetIndexToZero(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        setIndexToZeroHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ResultController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "ResultController::endPoint() - PanelID mismatch");
    }
}

void ResultController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        throw std::runtime_error("ProcessThread is still running");
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is still running");
    }
}

void ResultController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(THREAD_PROCESS)) {
        processThreadEndHandler(parent);
    }

    if (!tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        resultPreviewEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void ResultController::processThreadStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_PROCESS)) {
        throw std::runtime_error(
            "ResultController::processThreadStartHandler() - Thread is already "
            "running");
    }

    auto sessionData = shared->getSessionData();

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

void ResultController::toggleShowBoxHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowBox(show);
}

void ResultController::toggleShowLinesHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowIntersection(show);
}

void ResultController::toggleShowLanesHandler(wxEvtHandler *parent, bool show) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetShowLanes(show);
}

void ResultController::setIndexToZeroHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();
    if (tc->isThreadNullptr(THREAD_RESULT_PREVIEW)) {
        throw std::runtime_error("ResultPreviewThread is not running");
    }

    if (!tc->isThreadOwner(THREAD_RESULT_PREVIEW, panelID)) {
        throw std::runtime_error(
            "ResultPreviewThread is not owned by this controller");
    }

    auto thread = tc->getResultPreviewThread();
    thread->SetImageIndex(0);
}

void ResultController::cancelButtonHandler(wxEvtHandler *parent) {
    killAllThreads(parent);

    // remove all data from session
    auto sessionData = shared->getSessionData();
    // sessionData->removeAllignData();

    // auto tracking = sessionData->getTrackingData();
    // tracking.trackedRoi.clear();
    // sessionData->setTrackingData(tracking);

    sessionData->clearResultData();

    shared->setSessionData(*sessionData);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}
