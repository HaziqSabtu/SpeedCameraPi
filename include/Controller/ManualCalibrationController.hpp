#pragma once

#include "Model/SessionData.hpp"
#include <Model/SharedModel.hpp>

#define MCCPtr std::unique_ptr<ManualCalibrationController>

class ManualCalibrationController {
  public:
    ManualCalibrationController(ModelPtr sharedModel);
    ~ManualCalibrationController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_CreateTempSessionData(wxEvtHandler *parent);
    void e_RestoreSessionData(wxEvtHandler *parent);
    void e_SaveSessionData(wxEvtHandler *parent);

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ChangeToCalibrationPanel(wxEvtHandler *parent);

    void e_ChangeToLeft(wxEvtHandler *parent);
    void e_ChangeToRight(wxEvtHandler *parent);

    void e_SetPoint1(wxEvtHandler *parent, wxPoint point);
    void e_SetPoint2(wxEvtHandler *parent, wxPoint point);
    void e_SaveLine(wxEvtHandler *parent, wxPoint point);

    void e_ManualCalibStart(wxEvtHandler *parent);
    void e_ManualCalibEnd(wxEvtHandler *parent);

    void e_CalibPrevStart(wxEvtHandler *parent);
    void e_CalibPrevEnd(wxEvtHandler *parent);

    void e_RemoveLeft(wxEvtHandler *parent);
    void e_RemoveRight(wxEvtHandler *parent);

    void e_RemoveCalibData(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_MANUAL_CALIBRATION;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void changeToLeftHandler(wxEvtHandler *parent);
    void changeToRightHandler(wxEvtHandler *parent);

    void setPoint1Handler(wxEvtHandler *parent, cv::Point point);
    void setPoint2Handler(wxEvtHandler *parent, cv::Point point);
    void saveLineHandler(wxEvtHandler *parent, cv::Point point);

    void manualCalibStartHandler(wxEvtHandler *parent);
    void manualCalibEndHandler(wxEvtHandler *parent);

    void calibPrevStartHandler(wxEvtHandler *parent);
    void calibPrevEndHandler(wxEvtHandler *parent);

    void removeLeftHandler(wxEvtHandler *parent);
    void removeRightHandler(wxEvtHandler *parent);

    void createTempSessionDataHandler(wxEvtHandler *parent);
    void restoreSessionDataHandler(wxEvtHandler *parent);
    void saveSessionDataHandler(wxEvtHandler *parent);

    void removeCalibDataHandler(wxEvtHandler *parent);
};