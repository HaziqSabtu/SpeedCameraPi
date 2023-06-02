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

void SharedModel::setCamera(std::shared_ptr<CameraBase> camera) {
    this->camera = camera;
}

std::shared_ptr<CameraBase> SharedModel::getCamera() { return camera; }

void SharedModel::setThreadPool(std::shared_ptr<ThreadPool> threadPool) {
    this->threadPool = threadPool;
}

std::shared_ptr<ThreadPool> SharedModel::getThreadPool() { return threadPool; }