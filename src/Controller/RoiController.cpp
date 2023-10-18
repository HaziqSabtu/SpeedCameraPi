#include <Controller/RoiController.hpp>

#include <UI/Dialog/RemoveRoiDialog.hpp>

RoiController::RoiController(ResourcePtr shared)
    : BaseControllerWithTouch(shared) {
    panelID = currentPanelID;
}

RoiController::~RoiController() {}

void RoiController::e_ClearRect(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        clearRectHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RemoveRect(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        removeRectHandler(parent);
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

void RoiController::e_RoiThreadSave(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiThreadSaveHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RoiThreadCancel(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiThreadCancelHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RoiPreviewStart(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiPreviewStartHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::e_RoiPreviewEnd(wxEvtHandler *parent) {
    try {
        checkPreCondition();

        roiPreviewEndHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void RoiController::throwIfAnyThreadIsRunning() {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("ROIThread is running");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        throw std::runtime_error("ROIPreviewThread is running");
    }
}

void RoiController::killAllThreads(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        roiPreviewEndHandler(parent);
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        roiThreadCancelHandler(parent);
    }

    throwIfAnyThreadIsRunning();
}

void RoiController::clearRectHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint1(cv::Point(-1, -1));
    roiThread->setPoint2(cv::Point(-1, -1));
}

void RoiController::removeRectHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is running, cannot remove rect");
    }

    auto data = shared->getSessionData();

    if (data->isTrackingDataEmpty()) {
        throw std::runtime_error("Tracking data is empty");
    }

    auto wx = wxTheApp->GetTopWindow();
    auto dialog = new RemoveRoiDialog(wx);
    if (dialog->ShowModal() == wxID_NO) {
        return;
    }

    data->clearTrackingData();

    UpdateStatusEvent::Submit(parent, "ROI removed");
}

void RoiController::leftDownHandler(wxEvtHandler *parent, cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint2(cv::Point(-1, -1));
    roiThread->setPoint1(point);
}

void RoiController::leftMoveHandler(wxEvtHandler *parent, cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint2(point);
}

void RoiController::leftUpHandler(wxEvtHandler *parent, cv::Point point) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    auto roiThread = tc->getRoiThread();

    roiThread->setPoint2(point);

    if (roiThread->getRect().area() <= 0) {
        throw std::runtime_error("Invalid ROI");
    }

    auto realRect = roiThread->getRealRect();

    TrackingData data;
    data.roi = realRect;

    auto sessionData = shared->getSessionData();
    sessionData->setTrackingData(data);

    UpdateStatusEvent::Submit(parent, SC::STATUS_ROI_SELECTED);
}

void RoiController::roiThreadStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error(
            "RoiController::roiThreadStartHandler() - Capture data is empty");
    }

    throwIfAnyThreadIsRunning();

    tc->startRoiHandler(parent, data, panelID);
}

void RoiController::roiThreadSaveHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    auto roiThread = tc->getRoiThread();
    roiThread->Pause();

    if (roiThread->getRect().area() <= 0) {
        throw std::runtime_error("Invalid ROI");
    }

    auto realRect = roiThread->getRealRect();

    TrackingData data;
    data.roi = realRect;

    auto sessionData = shared->getSessionData();
    sessionData->setTrackingData(data);

    tc->endRoiHandler();
}

void RoiController::roiThreadCancelHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("RoiThread is already stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error("RoiThread is not owned by this controller");
    }

    tc->endRoiHandler();
}

void RoiController::roiPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    throwIfAnyThreadIsRunning();

    auto data = shared->getSessionData();

    tc->startRoiPreviewHandler(parent, data, panelID);
}

void RoiController::roiPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        throw std::runtime_error("RoiPreviewThread is not running");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI_PREVIEW, panelID)) {
        throw std::runtime_error(
            "RoiPreviewThread is not owned by this controller");
    }

    tc->endRoiPreviewHandler();
}

void RoiController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);

    auto data = shared->getSessionData();

    if (!data->isTrackingDataEmpty()) {
        return;
    }

    AppConfig c;
    auto config = c.GetThreadsConfig();
    auto startThread = config.autoRoi;

    if (!startThread) {
        return;
    }

    roiThreadStartHandler(parent);
}
