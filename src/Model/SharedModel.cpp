#include "Model/SharedModel.hpp"
#include "Model/SessionData.hpp"
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