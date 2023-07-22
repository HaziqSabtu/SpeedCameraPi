#include "Model/CalibrationModel.hpp"
#include "Algorithm/hsv_filter/BFS.hpp"
#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Algorithm/ransac_line/RansacLine.hpp"
#include "Thread/ThreadPool.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Thread/Thread_LoadFile.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include "Utils/DataStruct.hpp"
#include <Model/CalibrationModel.hpp>
#include <memory>
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

void CalibrationModel::initThreads() {
    captureThread = nullptr;
    calibrationThread = nullptr;
}

void CalibrationModel::deleteThreads() {
    if (captureThread != nullptr) {
        std::unique_ptr<CameraBase> camera = captureThread->getCamera();
        shared->setCamera(camera);
        captureThread = stopAndDeleteThread(captureThread);
    }

    if (calibrationThread != nullptr) {
        std::unique_ptr<CameraBase> camera = calibrationThread->getCamera();
        shared->setCamera(camera);
    }
    calibrationThread = stopAndDeleteThread(calibrationThread);
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
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        switchPanelHandler(parent, PanelID::PANEL_CAPTURE);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToManualPanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        switchPanelHandler(parent, PanelID::PANEL_MANUAL_CALIBRATION);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_ChangeToColorPanel(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        switchPanelHandler(parent, PanelID::PANEL_COLOR_CALIBRATION);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_StartCalibration(wxEvtHandler *parent) {
    try {

        checkPreCondition();

        startCalibrationHandler(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void CalibrationModel::e_SetPoint(wxEvtHandler *parent, wxPoint point) {
    try {

        checkPreCondition();

        setPointHandler(parent, Utils::wxPointToCvPoint(point));

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
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

void CalibrationModel::switchPanelHandler(wxEvtHandler *parent,
                                          PanelID target) {
    if (!isRequirementFulfilled()) {
        throw std::runtime_error("Requirement is not fulfilled");
    }

    deleteThreads();

    ChangePanelData data(this->panelID, target);
    ChangePanelEvent::Submit(parent, data);
}

void CalibrationModel::startCalibrationHandler(wxEvtHandler *parent) {
    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }

    if (calibrationThread != nullptr || captureThread != nullptr) {
        throw std::runtime_error("calibrationThread is already running");
    }

    std::unique_ptr<CameraBase> camera = shared->getCamera();

    HSVFilter filter;
    BFS bfs;
    RansacLine ransacLine(500, 50, 8);
    calibrationThread =
        initCalibrationThread(parent, camera, filter, bfs, ransacLine);
    calibrationThread->Run();
}

bool CalibrationModel::isRequirementFulfilled() { return true; }

void CalibrationModel::startCaptureHandler(wxEvtHandler *parent) {
    if (!shared->isCameraAvailable()) {
        throw std::runtime_error("Camera is not available");
    }
    if (captureThread != nullptr || calibrationThread != nullptr) {
        throw std::runtime_error("captureThread is already running");
    }

    std::unique_ptr<CameraBase> camera = shared->getCamera();
    captureThread = initCaptureThread(parent, camera);
    captureThread->Run();
}

void CalibrationModel::endCaptureHandler() {
    captureThread->Pause();
    std::unique_ptr<CameraBase> camera = captureThread->getCamera();
    shared->setCamera(camera);
    captureThread = stopAndDeleteThread(captureThread);
}

void CalibrationModel::setPointHandler(wxEvtHandler *parent, cv::Point point) {
    if (calibrationThread == nullptr) {
        throw std::runtime_error("calibrationThread is not running");
    }

    calibrationThread->setPoint(point);
}

CaptureThread *
CalibrationModel::initCaptureThread(wxEvtHandler *parent,
                                    std::unique_ptr<CameraBase> &camera) {
    return new CaptureThread(parent, camera);
}

CalibrationThread *CalibrationModel::initCalibrationThread(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    HSVFilter &filter, BFS &bfs, RansacLine &ransac) {
    return new CalibrationThread(parent, camera, filter, bfs, ransac);
}