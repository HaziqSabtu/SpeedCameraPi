#include "Model/SharedModel.hpp"
#include <Controller/ColorCalibrationController.hpp>

ColorCalibrationController::ColorCalibrationController(ModelPtr sharedModel)
    : shared(sharedModel) {}

ColorCalibrationController::~ColorCalibrationController() {}

void ColorCalibrationController::checkPreCondition() {
    if (panelID != shared->sessionData.currentPanelID) {
        throw std::runtime_error(
            "ColorCalibrationController::endPoint() - PanelID mismatch");
    }
}

void ColorCalibrationController::e_ChangeToCapturePanel(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void ColorCalibrationController::e_ChangeToCalibrationPanel(
    wxEvtHandler *parent) {
    try {
        checkPreCondition();
        ChangePanelData data(this->panelID, PanelID::PANEL_CALIBRATION);
        ChangePanelEvent::Submit(parent, data);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}