#include <Controller/ManualCalibrationController.hpp>

ManualCalibrationController::ManualCalibrationController(
    std::shared_ptr<SharedModel> s)
    : shared(s) {}

ManualCalibrationController::~ManualCalibrationController() {}

void ManualCalibrationController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "ManualCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ManualCalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ManualCalibrationController::e_ChangeToCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}