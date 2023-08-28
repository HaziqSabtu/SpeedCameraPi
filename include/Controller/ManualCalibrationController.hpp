#pragma once

#include <Algorithm/Struct/D_Line.hpp>

#include <Controller/BaseController.hpp>

#include <Event/Event_UpdateState.hpp>

#include <Model/AppState.hpp>
#include <Model/CalibrationData.hpp>
#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <Thread/Thread_ManualCalib.hpp>

#include <UI/Dialog/CancelDialog.hpp>

#include <Utils/wxUtils.hpp>

#include <wx/event.h>

#define MCCPtr std::unique_ptr<ManualCalibrationController>

class ManualCalibrationController : public BaseController {
  public:
    ManualCalibrationController(ModelPtr sharedModel);
    ~ManualCalibrationController();

    void e_ChangeToLeft(wxEvtHandler *parent);
    void e_ChangeToRight(wxEvtHandler *parent);

    void e_SetPoint1(wxEvtHandler *parent, wxPoint point);
    void e_SetPoint2(wxEvtHandler *parent, wxPoint point);
    void e_SaveLine(wxEvtHandler *parent, wxPoint point);

    void e_ManualCalibStart(wxEvtHandler *parent);
    void e_ManualCalibEnd(wxEvtHandler *parent);

    void e_ManualCalibCaptureStart(wxEvtHandler *parent);
    void e_ManualCalibCaptureEnd(wxEvtHandler *parent);

    void e_CalibPrevStart(wxEvtHandler *parent);
    void e_CalibPrevEnd(wxEvtHandler *parent);

    void e_CalibCapturePrevStart(wxEvtHandler *parent);
    void e_CalibCapturePrevEnd(wxEvtHandler *parent);

    void e_RemoveLeft(wxEvtHandler *parent);
    void e_RemoveRight(wxEvtHandler *parent);

    void e_RemoveCalibData(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_MANUAL_CALIBRATION;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void changeToLeftHandler(wxEvtHandler *parent);
    void changeToRightHandler(wxEvtHandler *parent);

    void setPoint1Handler(wxEvtHandler *parent, cv::Point point);
    void setPoint2Handler(wxEvtHandler *parent, cv::Point point);
    void saveLineHandler(wxEvtHandler *parent, cv::Point point);

    void manualCalibStartHandler(wxEvtHandler *parent);
    void manualCalibEndHandler(wxEvtHandler *parent);

    void manualCalibCaptureStartHandler(wxEvtHandler *parent);
    void manualCalibCaptureEndHandler(wxEvtHandler *parent);

    void calibPrevStartHandler(wxEvtHandler *parent);
    void calibPrevEndHandler(wxEvtHandler *parent);

    void calibCapturePrevStartHandler(wxEvtHandler *parent);
    void calibCapturePrevEndHandler(wxEvtHandler *parent);

    void removeLeftHandler(wxEvtHandler *parent);
    void removeRightHandler(wxEvtHandler *parent);

    void removeCalibDataHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent) override;
};