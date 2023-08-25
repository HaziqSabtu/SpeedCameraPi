#include "Event/Event_UpdateState.hpp"
#include <Controller/TrimDataController.hpp>

#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_ID.hpp"
#include "Thread/Thread_TrimData.hpp"
#include "UI/Dialog/CancelDialog.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/CommonUtils.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/wxUtils.hpp"
#include <memory>
#include <vector>
#include <wx/event.h>
#include <wx/object.h>

TrimDataController::TrimDataController(ModelPtr sharedModel)
    : shared(sharedModel) {}

TrimDataController::~TrimDataController() {}

void TrimDataController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_PanelShow(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        panelShowHandler(parent);

        e_UpdateState(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_CreateTempSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_OKButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        okButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_TrimDataStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        trimDataStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_TrimDataEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        trimDataEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_ReplayStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        replayStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_ReplayEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        replayEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_IncrementStartPos(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        incrementStartPosHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_DecrementStartPos(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        decrementStartPosHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_IncrementEndPos(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        incrementEndPosHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_DecrementEndPos(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        decrementEndPosHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::e_PreviewCurrentRange(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        previewCurrentRangeHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void TrimDataController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error(
            "TrimDataController::endPoint() - PanelID mismatch");
    }
}

void TrimDataController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is running");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_REPLAY)) {
        throw std::runtime_error("ReplayThread is running");
    }
}

void TrimDataController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        trimDataEndHandler(parent);
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_REPLAY)) {
        replayEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void TrimDataController::createTempSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

void TrimDataController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

void TrimDataController::restoreSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

void TrimDataController::okButtonHandler(wxEvtHandler *parent) {

    killAllThreads(parent);

    saveSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void TrimDataController::cancelButtonHandler(wxEvtHandler *parent) {

    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void TrimDataController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);
}

void TrimDataController::trimDataStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();
    tc->startTrimDataHandler(parent, data, panelID);
}

void TrimDataController::trimDataEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();
    thread->Pause();

    thread->processTrimData();

    tc->endTrimDataHandler();

    wxString msg = wxString("TrimData Success");
    UpdateStatusEvent::Submit(parent, msg);
}

void TrimDataController::replayStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();
    tc->startReplayHandler(parent, data, panelID);

    wxString msg = wxString("Replay Started");
    UpdateStatusEvent::Submit(parent, msg);
}

void TrimDataController::replayEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_REPLAY)) {
        throw std::runtime_error("ReplayThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_REPLAY, panelID)) {
        throw std::runtime_error("ReplayThread is not owned by this panel");
    }

    auto thread = tc->getReplayThread();
    thread->Pause();

    tc->endReplayHandler();

    wxString msg = wxString("Replay Ended");
    UpdateStatusEvent::Submit(parent, msg);

    e_UpdateState(parent);
}

void TrimDataController::incrementStartPosHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() != TRIM_START) {
        thread->setStatus(TRIM_START);
    }

    if (!thread->isStartIncrementable()) {
        return;
    }

    thread->incrementStartPos();
}

void TrimDataController::decrementStartPosHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() != TRIM_START) {
        thread->setStatus(TRIM_START);
    }

    if (!thread->isStartDecrementable()) {
        return;
    }

    thread->decrementStartPos();
}

void TrimDataController::incrementEndPosHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() != TRIM_END) {
        thread->setStatus(TRIM_END);
    }

    if (!thread->isEndIncrementable()) {
        return;
    }

    thread->incrementEndPos();
}

void TrimDataController::decrementEndPosHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() != TRIM_END) {
        thread->setStatus(TRIM_END);
    }

    if (!thread->isEndDecrementable()) {
        return;
    }

    thread->decrementEndPos();
}

void TrimDataController::previewCurrentRangeHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_TRIM_DATA, panelID)) {
        throw std::runtime_error("TrimDataThread is not owned by this panel");
    }

    auto thread = tc->getTrimDataThread();

    if (thread->getStatus() != TRIM_PREVIEW) {
        thread->setStatus(TRIM_PREVIEW);
    }
}

void TrimDataController::e_RestoreDefault(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto tempCapture = temp->getCaptureData();
    data->setCaptureData(tempCapture);

    shared->setSessionData(*data);

    wxString msg = wxString("Restore Success");
    UpdateStatusEvent::Submit(parent, msg);
}
