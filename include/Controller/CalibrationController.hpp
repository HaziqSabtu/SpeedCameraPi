#pragma once

#include "Algorithm/hsv_filter/HSVFilter.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "UI/Button/Button_ToggleCamera.hpp"
#include "UI/Button/Button_wState.hpp"
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

    void e_RemoveCalibData(wxEvtHandler *parent);

    void e_SetPoint(wxEvtHandler *parent, wxPoint point);

    void e_CameraStart(wxEvtHandler *parent);
    void e_CameraEnd(wxEvtHandler *parent);

    void e_CalibrationStart(wxEvtHandler *parent);
    void e_CalibrationSave(wxEvtHandler *parent);
    void e_CalibrationEnd(wxEvtHandler *parent);

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ChangeToManualPanel(wxEvtHandler *parent);

    void e_ChangeToColorPanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_CALIBRATION;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startCalibrationHandler(wxEvtHandler *parent);
    void saveCalibrationHandler(wxEvtHandler *parent);
    void endCalibrationHandler();

    void setPointHandler(wxEvtHandler *parent, cv::Point point);
};