#include "Model/SharedModel.hpp"
#include "Model/AppState.hpp"
#include "Model/SessionData.hpp"
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

void SharedModel::setCamera(std::unique_ptr<CameraBase> &camera) {
    this->camera = std::move(camera);
}

std::unique_ptr<CameraBase> SharedModel::getCamera() {
    return camera == nullptr ? nullptr : std::move(camera);
}

bool SharedModel::isCameraAvailable() { return camera != nullptr; }

void SharedModel::setThreadPool(std::shared_ptr<ThreadPool> threadPool) {
    this->threadPool = threadPool;
}

std::shared_ptr<ThreadPool> SharedModel::getThreadPool() { return threadPool; }

void SharedModel::setThreadController(
    std::shared_ptr<ThreadController> threadController) {
    this->threadController = threadController;
}

std::shared_ptr<ThreadController> SharedModel::getThreadController() {
    return threadController;
}

void SharedModel::killAllThreads() {
    auto tc = getThreadController();

    if (!tc->isThreadNullptr(ThreadID::THREAD_CAPTURE)) {
        auto thread = tc->getCaptureThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_LOAD_CAPTURE)) {
        auto thread = tc->getLoadCaptureThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endLoadCaptureHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION)) {
        auto thread = tc->getCalibrationThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCalibrationHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_CALIBRATION_PREVIEW)) {
        auto thread = tc->getCalibPreviewThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endCalibPreviewHandler();
    }

    if (!tc->isThreadNullptr(ThreadID::THREAD_MANUAL_CALIBRATION)) {
        auto thread = tc->getManualCalibrationThread();
        thread->Pause();

        auto camera = thread->getCamera();
        setCamera(camera);

        tc->endManualCalibrationHandler();
    }
}

DataPtr SharedModel::getSessionData() {
    return std::make_shared<SessionData>(sessionData);
}
