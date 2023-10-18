#include <Controller/TrimDataController.hpp>

TrimDataController::TrimDataController(ResourcePtr shared)
    : BaseController(shared) {
    panelID = currentPanelID;
}

TrimDataController::~TrimDataController() {}

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

void TrimDataController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        throw std::runtime_error("TrimDataThread is running");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CAPTURE_PREVIEW)) {
        throw std::runtime_error("ReplayThread is running");
    }
}

void TrimDataController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        trimDataEndHandler(parent);
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CAPTURE_PREVIEW)) {
        replayEndHandler(parent);
    }

    throwIfAnyThreadIsRunning();
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
    tc->startCapturePreviewHandler(parent, data, panelID);

    wxString msg = wxString("Replay Started");
    UpdateStatusEvent::Submit(parent, msg);
}

void TrimDataController::replayEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_CAPTURE_PREVIEW)) {
        throw std::runtime_error("ReplayThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_CAPTURE_PREVIEW, panelID)) {
        throw std::runtime_error("ReplayThread is not owned by this panel");
    }

    auto thread = tc->getCapturePreviewThread();
    thread->Pause();

    tc->endCapturePreviewHandler();

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
