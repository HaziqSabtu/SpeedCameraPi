#pragma once

#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Model/SharedModel.hpp>
#include <memory>
#include <wx/event.h>
#include <wx/thread.h>

#define CLCPtr std::unique_ptr<CalibrationController>

class CalibrationController {
  public:
    CalibrationController(ModelPtr sharedModel);
    ~CalibrationController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_PanelShow(wxEvtHandler *parent);

    void e_CreateTempSessionData(wxEvtHandler *parent);
    void e_RestoreSessionData(wxEvtHandler *parent);
    void e_SaveSessionData(wxEvtHandler *parent);

    void e_RemoveCalibData(wxEvtHandler *parent);

    void e_SetPoint(wxEvtHandler *parent, wxPoint point);
    void e_ClearPoint(wxEvtHandler *parent);

    void e_CalibrationStart(wxEvtHandler *parent);
    void e_CalibrationEnd(wxEvtHandler *parent);

    void e_CalibrationCaptureStart(wxEvtHandler *parent);
    void e_CalibrationCaptureEnd(wxEvtHandler *parent);

    void e_CalibrationPreviewStart(wxEvtHandler *parent);
    void e_CalibrationPreviewEnd(wxEvtHandler *parent);

    void e_CalibrationCapturePreviewStart(wxEvtHandler *parent);
    void e_CalibrationCapturePreviewEnd(wxEvtHandler *parent);

    void e_OKButtonHandler(wxEvtHandler *parent);
    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_ChangeToManualPanel(wxEvtHandler *parent);
    void e_ChangeToColorPanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_CALIBRATION;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void throwIfAnyThreadIsRunning();

    void killAllThreads(wxEvtHandler *parent);

    void saveCalibrationData(wxEvtHandler *parent,
                             BaseCalibrationThread *thread);

    void calibrationStartHandler(wxEvtHandler *parent);
    void calibrationEndHandler(wxEvtHandler *parent);

    void calibrationCaptureStartHandler(wxEvtHandler *parent);
    void calibrationCaptureEndHandler(wxEvtHandler *parent);

    void calibrationPreviewStartHandler(wxEvtHandler *parent);
    void calibrationPreviewEndHandler(wxEvtHandler *parent);

    void calibrationCapturePreviewStartHandler(wxEvtHandler *parent);
    void calibrationCapturePreviewEndHandler(wxEvtHandler *parent);

    void setPointHandler(wxEvtHandler *parent, cv::Point point);
    void clearPointHandler(wxEvtHandler *parent);

    void createTempSessionDataHandler(wxEvtHandler *parent);
    void restoreSessionDataHandler(wxEvtHandler *parent);
    void saveSessionDataHandler(wxEvtHandler *parent);

    void okButtonHandler(wxEvtHandler *parent);
    void cancelButtonHandler(wxEvtHandler *parent);

    void changeToManualPanelHandler(wxEvtHandler *parent);
    void changeToColorPanelHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent);
};