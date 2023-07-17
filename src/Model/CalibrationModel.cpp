#include "Model/CalibrationModel.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include <Model/CalibrationModel.hpp>
#include <vector>
#include <wx/event.h>
#include <wx/object.h>

CalibrationModel::CalibrationModel(std::shared_ptr<SharedModel> sharedModel)
    : shared(sharedModel) {
    initThreads();
}

CalibrationModel::~CalibrationModel() {
    try {
        deleteThreads();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void CalibrationModel::initThreads() { captureThread = nullptr; }

void CalibrationModel::deleteThreads() {
    captureThread = stopAndDeleteThread(captureThread);
}

void CalibrationModel::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "CalibrationModel::endPoint() - PanelID mismatch");
    }
}

void CalibrationModel::e_ToggleCamera(wxEvtHandler *parent, bool state) {
    try {

        checkPreCondition();

        !state ? startCaptureHandler(parent) : endCaptureHandler();

    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

void CalibrationModel::e_ChangePanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        switchPanelHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

template <typename T>
T *CalibrationModel::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}

void CalibrationModel::switchPanelHandler(wxEvtHandler *parent) {
    if (!isRequirementFulfilled()) {
        throw std::runtime_error("Requirement is not fulfilled");
    }

    deleteThreads();

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);

    ChangePanelEvent changePanelEvent(c_CHANGE_PANEL_EVENT, CHANGE_OK);
    changePanelEvent.SetPanelData(data);
    wxPostEvent(parent, changePanelEvent);
}

bool CalibrationModel::isRequirementFulfilled() { return true; }

void CalibrationModel::startCaptureHandler(wxEvtHandler *parent) {
    if (shared->getCamera() == nullptr) {
        throw std::runtime_error("Camera is not initialized");
    }
    if (captureThread != nullptr) {
        throw std::runtime_error("captureThread is already running");
    }

    captureThread = initCaptureThread(parent, shared->getCamera());
    captureThread->Run();
}

void CalibrationModel::endCaptureHandler() {
    captureThread = stopAndDeleteThread(captureThread);
}

wxThread *
CalibrationModel::initCaptureThread(wxEvtHandler *parent,
                                    std::shared_ptr<CameraBase> camera) {
    return new CaptureThread(parent, camera);
}