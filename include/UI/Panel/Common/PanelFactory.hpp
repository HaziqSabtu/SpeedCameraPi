#pragma once

#include "Controller/ControllerFactory.hpp"
#include "Controller/LaneCalibrationController.hpp"
#include "Model/SessionData.hpp"
#include "UI/Panel/CapturePanel/Panel.hpp"
#include "UI/Panel/ColorCalibrationPanel/Panel.hpp"
#include "UI/Panel/DistanceCalibrationPanel/Panel.hpp"
#include "UI/Panel/LaneCalibrationPanel/Panel.hpp"
#include "UI/Panel/LaneManualCalibrationPanel/Panel.hpp"
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

        if (panelID == PANEL_LANE_CALIBRATION) {
            return createLaneCalibrationPanel(parent);
        }

        if (panelID == PANEL_LANE_MANUAL_CALIBRATION) {
            return createLaneManualCalibrationPanel(parent);
        }

        if (panelID == PANEL_DISTANCE_CALIBRATION) {
            return createDistanceCalibrationPanel(parent);
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

    LaneCalibrationPanel *createLaneCalibrationPanel(wxWindow *parent) {
        LCCPtr controller =
            controllerFactory->createLaneCalibrationController();
        return new LaneCalibrationPanel(parent, Enum::LC_Panel_ID, controller);
    }

    LaneManualCalibrationPanel *
    createLaneManualCalibrationPanel(wxWindow *parent) {
        LMCPtr controller =
            controllerFactory->createLaneManualCalibrationController();
        return new LaneManualCalibrationPanel(parent, Enum::LM_Panel_ID,
                                              controller);
    }

    DistanceCalibrationPanel *createDistanceCalibrationPanel(wxWindow *parent) {
        DCCPtr controller =
            controllerFactory->createDistanceCalibrationController();
        return new DistanceCalibrationPanel(parent, Enum::DC_Panel_ID,
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