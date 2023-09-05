#pragma once

#include "Controller/ControllerFactory.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/CalibrationPanel/Panel.hpp"
#include "UI/Panel/CapturePanel/Panel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "UI/Panel/ManualCalibrationPanel/Panel.hpp"
#include "UI/Panel/ResultPanel/Panel.hpp"
#include "UI/Panel/RoiPanel/Panel.hpp"
#include "UI/Panel/TrimDataPanel/Panel.hpp"

#define PanelFactoryPtr std::shared_ptr<PanelFactory>

class PanelFactory {
  public:
    PanelFactory(CtrlFactoryPtr controllerFactory)
        : controllerFactory(controllerFactory) {};
    ~PanelFactory() {};

    wxPanel *createPanel(wxWindow *parent, PanelID panelID) {
        if (panelID == PANEL_CAPTURE) {
            return createCapturePanel(parent);
        }

        if (panelID == PANEL_ROI) {
            return createRoiPanel(parent);
        }

        if (panelID == PANEL_CALIBRATION) {
            return createCalibrationPanel(parent);
        }

        if (panelID == PANEL_MANUAL_CALIBRATION) {
            return createManualCalibrationPanel(parent);
        }

        if (panelID == PANEL_COLOR_CALIBRATION) {
            return createColorCalibrationPanel(parent);
        }

        if (panelID == PANEL_TRIM_DATA) {
            return createTrimDataPanel(parent);
        }

        if (panelID == PANEL_RESULT) {
            return createResultPanel(parent);
        }

        throw std::runtime_error("PanelFactory::createPanel: Unknown panelID");
    }

    CapturePanel *createCapturePanel(wxWindow *parent) {
        CPCPtr controller = controllerFactory->createCaptureController();
        return new CapturePanel(parent, Enum::CP_Panel_ID, controller);
    }

    RoiPanel *createRoiPanel(wxWindow *parent) {
        ROCPtr controller = controllerFactory->createRoiController();
        return new RoiPanel(parent, Enum::RO_Panel_ID, controller);
    }

    CalibrationPanel *createCalibrationPanel(wxWindow *parent) {
        CLCPtr controller = controllerFactory->createCalibrationController();
        return new CalibrationPanel(parent, Enum::CL_Panel_ID, controller);
    }

    ManualCalibrationPanel *createManualCalibrationPanel(wxWindow *parent) {
        MCCPtr controller =
            controllerFactory->createManualCalibrationController();
        return new ManualCalibrationPanel(parent, Enum::MC_Panel_ID,
                                          controller);
    }

    ColorCalibrationPanel *createColorCalibrationPanel(wxWindow *parent) {
        CCCPtr controller =
            controllerFactory->createColorCalibrationController();
        return new ColorCalibrationPanel(parent, Enum::CC_Panel_ID, controller);
    }

    TrimDataPanel *createTrimDataPanel(wxWindow *parent) {
        TDCPtr controller = controllerFactory->createTrimDataController();
        return new TrimDataPanel(parent, Enum::TR_Panel_ID, controller);
    }

    ResultPanel *createResultPanel(wxWindow *parent) {
        RSCPtr controller = controllerFactory->createResultController();
        return new ResultPanel(parent, Enum::RE_Panel_ID, controller);
    }

  private:
    CtrlFactoryPtr controllerFactory;
};