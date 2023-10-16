#include "Model/SharedModel.hpp"
#include "Model/AppState.hpp"
#include "Model/ExtraModel.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Controller.hpp"
#include "Thread/Thread_ID.hpp"
#include <memory>
#include <wx/event.h>

SharedModel::SharedModel() : camera(nullptr), threadPool(nullptr) {}

SharedModel::~SharedModel() {
    try {
        if (camera != nullptr) {
            camera->stop();
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void SharedModel::setCamera(CameraPtr &camera) {
    this->camera = std::move(camera);
}

CameraPtr SharedModel::getCamera() {
    return camera == nullptr ? nullptr : std::move(camera);
}

bool SharedModel::isCameraAvailable() { return camera != nullptr; }

void SharedModel::setThreadPool(POOLPtr threadPool) {
    this->threadPool = threadPool;
}

POOLPtr SharedModel::getThreadPool() { return threadPool; }

void SharedModel::setThreadController(
    std::shared_ptr<ThreadController> threadController) {
    this->threadController = threadController;
}

std::shared_ptr<ThreadController> SharedModel::getThreadController() {
    return threadController;
}

void SharedModel::killAllThreads() {
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

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION_CAMERA)) {
        auto thread = tc->getCalibrationCameraThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCalibrationCameraHandler();
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

    if (!tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION_CAMERA)) {
        auto thread = tc->getManualCalibrationCameraThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endManualCalibrationCameraHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION_CAPTURE)) {
        auto thread = tc->getManualCalibrationCaptureThread();
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
DataPtr SharedModel::getSessionData() {
    return DataPtr(&sessionData, [](SessionData *) {});
}

DataPtr SharedModel::getTempSessionData() {
    return DataPtr(&tempSessionData, [](SessionData *) {});
}

void SharedModel::setSessionData(SessionData data) {
    sessionData = data.clone();
}

void SharedModel::resetSessionData() { sessionData = SessionData(); }

void SharedModel::setTempSessionData(SessionData data) {
    tempSessionData = data.clone();
    // tempSessionData = data;
}

bool SharedModel::isSessionDataChanged() {
    return sessionData != tempSessionData;
}

// void SharedModel::setCCExtraModel(ColorCalibExtraModel ccExtraModel) {
//     this->ccExtraModel = ccExtraModel.clone();
// }

// CCModelPtr SharedModel::getCCExtraModel() {
//     return std::shared_ptr<ColorCalibExtraModel>(&ccExtraModel,
//                                                  [](ColorCalibExtraModel *) {});
// }