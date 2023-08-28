#include <Controller/RoiController.hpp>

RoiController::RoiController(ModelPtr sharedModel)
    : BaseController(sharedModel) {
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

void RoiController::e_SaveRect(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();

        saveRectHandler(parent, Utils::wxPointToCvPoint(point));
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

void RoiController::removeRectHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::removeRectHandler() - Thread is  running");
    }

    auto data = shared->getSessionData();

    if (data->isTrackingDataEmpty()) {
        throw std::runtime_error(
            "RoiController::removeRectHandler() - RoiData is empty");
    }

    data->clearTrackingData();
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

void RoiController::saveRectHandler(wxEvtHandler *parent, cv::Point point) {
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

    cv::Rect rect = roiThread->getRect();

    if (rect.width <= 0 || rect.height <= 0) {
        throw std::runtime_error(
            "RoiController::roiThreadSaveHandler() - Invalid ROI");
    }

    AppConfig c;

    auto pConfig = c.GetPreviewConfig();
    int pWidth = pConfig.width;
    int pHeight = pConfig.height;
    cv::Size src(pWidth, pHeight);

    auto cConfig = c.GetCameraConfig();
    int width = cConfig.Camera_Width;
    int height = cConfig.Camera_Height;
    cv::Size dst(width, height);

    auto realRect = Utils::scaleRect(rect, src, dst);

    TrackingData data;
    data.roi = realRect;

    auto sessionData = shared->getSessionData();
    sessionData->setTrackingData(data);
}

void RoiController::roiThreadStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    auto data = shared->getSessionData();

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error(
            "RoiController::roiThreadStartHandler() - Capture data is empty");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::roiThreadStartHandler() - Thread is already "
            "running");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        throw std::runtime_error(
            "RoiController::roiThreadStartHandler() - Roi Preview is already "
            "running");
    }

    tc->startRoiHandler(parent, data, panelID);
}

void RoiController::roiThreadSaveHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::roiThreadSaveHandler() - Thread is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::roiThreadSaveHandler() - Thread is not owned by "
            "this controller");
    }

    auto roiThread = tc->getRoiThread();
    roiThread->Pause();

    cv::Rect rect = roiThread->getRect();

    if (rect.width <= 0 || rect.height <= 0) {
        throw std::runtime_error(
            "RoiController::roiThreadSaveHandler() - Invalid ROI");
    }

    // TODO: Do this in Thread
    AppConfig c;

    auto pConfig = c.GetPreviewConfig();
    int pWidth = pConfig.width;
    int pHeight = pConfig.height;
    cv::Size src(pWidth, pHeight);

    auto cConfig = c.GetCameraConfig();
    int width = cConfig.Camera_Width;
    int height = cConfig.Camera_Height;
    cv::Size dst(width, height);

    auto realRect = Utils::scaleRect(rect, src, dst);

    TrackingData data;
    data.roi = realRect;

    auto sessionData = shared->getSessionData();
    sessionData->setTrackingData(data);

    tc->endRoiHandler();
}
void RoiController::roiThreadCancelHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error(
            "RoiController::roiThreadCancelHandler() - Thread is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI, panelID)) {
        throw std::runtime_error(
            "RoiController::roiThreadCancelHandler() - Thread is not owned by "
            "this controller");
    }

    tc->endRoiHandler();
}

void RoiController::roiPreviewStartHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        throw std::runtime_error("ROI Thread is running");
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        throw std::runtime_error(
            "RoiController::roiPreviewStartHandler() - Roi Preview is already "
            "running");
    }

    auto data = shared->getSessionData();

    tc->startRoiPreviewHandler(parent, data, panelID);
}

void RoiController::roiPreviewEndHandler(wxEvtHandler *parent) {
    auto tc = shared->getThreadController();

    if (tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        throw std::runtime_error(
            "RoiController::roiPreviewEndHandler() - Roi Preview is already "
            "stopped");
    }

    if (!tc->isThreadOwner(ThreadID::THREAD_ROI_PREVIEW, panelID)) {
        throw std::runtime_error(
            "RoiController::roiPreviewEndHandler() - Roi Preview is not owned "
            "by this controller");
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
