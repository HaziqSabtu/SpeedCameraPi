#include <Model/SharedResource.hpp>

#include <Event/Event.hpp>

#include <memory>
#include <wx/event.h>

/**
 * @brief Construct a new Shared Resource:: Shared Resource object
 *
 */
SharedResource::SharedResource() : camera(nullptr), threadPool(nullptr) {}

/**
 * @brief Destroy the Shared Resource:: Shared Resource object
 *
 */
SharedResource::~SharedResource() {
    try {
        if (camera != nullptr) {
            camera->stop();
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * @brief Set the Camera pointer
 *
 * @param camera unique_ptr to the Camera
 */
void SharedResource::setCamera(CameraPtr &camera) {
    this->camera = std::move(camera);
}

/**
 * @brief Get the Camera pointer
 *
 * @return CameraPtr unique_ptr to the Camera
 */
CameraPtr SharedResource::getCamera() {
    return camera == nullptr ? nullptr : std::move(camera);
}

/**
 * @brief Check if the Camera is available
 *
 * @return true if available
 * @return false if not available
 */
bool SharedResource::isCameraAvailable() { return camera != nullptr; }

/**
 * @brief Set the ThreadPool object
 *
 * @param threadPool shared_ptr to the ThreadPool
 */
void SharedResource::setThreadPool(POOLPtr threadPool) {
    this->threadPool = threadPool;
}

/**
 * @brief Get the ThreadPool object
 *
 * @return POOLPtr shared_ptr to the ThreadPool
 */
POOLPtr SharedResource::getThreadPool() { return threadPool; }

/**
 * @brief Set the ThreadController object
 *
 * @param threadController shared_ptr to the ThreadController
 */
void SharedResource::setThreadController(
    std::shared_ptr<ThreadController> threadController) {
    this->threadController = threadController;
}

/**
 * @brief Get the ThreadController object
 *
 * @return std::shared_ptr<ThreadController> shared_ptr to the ThreadController
 */
std::shared_ptr<ThreadController> SharedResource::getThreadController() {
    return threadController;
}

/**
 * @brief Kill all threads
 *
 */
void SharedResource::killAllThreads() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_CAMERA_PREVIEW)) {
        auto thread = tc->getCameraPreviewThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCameraPreviewHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_LOAD_CAPTURE)) {
        auto thread = tc->getLoadCaptureThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endLoadCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_LANE_CALIBRATION_CAMERA)) {
        auto thread = tc->getLaneCalibrationCameraThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endLaneCalibrationCameraHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION_PREVIEW_CAMERA)) {
        auto thread = tc->getCalibrationPreviewCameraThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCalibrationPreviewCameraHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION_PREVIEW_CAPTURE)) {
        auto thread = tc->getCalibrationPreviewCaptureThread();
        thread->Pause();

        tc->endCalibrationPreviewCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAMERA)) {
        auto thread = tc->getLaneManualCalibrationCameraThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endLaneManualCalibrationCameraHandler();
    }

    if (!tc->isThreadNullptr(
            ThreadID::THREAD_LANE_MANUAL_CALIBRATION_CAPTURE)) {
        auto thread = tc->getLaneManualCalibrationCaptureThread();
        thread->Pause();

        tc->endManualCalibrationCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_COLOR_CALIBRATION)) {
        auto thread = tc->getColorCalibrationThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endColorCalibrationHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_COLOR_CALIBRATION_PREVIEW)) {
        auto thread = tc->getColorCalibPreviewThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endColorCalibrationPreviewHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI)) {
        auto thread = tc->getRoiThread();
        thread->Pause();

        tc->endRoiHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_ROI_PREVIEW)) {
        auto thread = tc->getRoiPreviewThread();
        thread->Pause();

        tc->endRoiPreviewHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_TRIM_DATA)) {
        auto thread = tc->getTrimDataThread();
        thread->Pause();

        tc->endTrimDataHandler();
    }
}

// return a shared_ptr to the SessionData object WITHOUT copying it
// e.g. is pointing to the same object as the one in SharedModel
// if want to deep copy -> DataPtr(sessionData)

/**
 * @brief Return a shared_ptr to the SessionData object WITHOUT copying it
 *
 * @return DataPtr
 */
DataPtr SharedResource::getSessionData() {
    return DataPtr(&sessionData, [](SessionData *) {});
}

/**
 * @brief Return a shared_ptr to the SessionData object WITHOUT copying it
 *
 * @return DataPtr
 */
DataPtr SharedResource::getTempSessionData() {
    return DataPtr(&tempSessionData, [](SessionData *) {});
}

/**
 * @brief Set the SessionData object
 *
 * @param data SessionData object
 */
void SharedResource::setSessionData(SessionData data) {
    sessionData = data.clone();
}

/**
 * @brief Reset the SessionData object
 *
 */
void SharedResource::resetSessionData() { sessionData = SessionData(); }

/**
 * @brief Set the Temp Session Data object
 *
 * @param data SessionData object
 */
void SharedResource::setTempSessionData(SessionData data) {
    tempSessionData = data.clone();
}

/**
 * @brief Check if the SessionData object has changed
 *
 * @return true if changed
 * @return false if not changed
 */
bool SharedResource::isSessionDataChanged() {
    return sessionData != tempSessionData;
}