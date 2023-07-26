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

class CalibrationModel {
  public:
    CalibrationModel(std::shared_ptr<SharedModel> sharedModel);
    ~CalibrationModel();

    void e_UpdateState(wxEvtHandler *parent);

    void e_SetPoint(wxEvtHandler *parent, wxPoint point);

    void e_CameraStart(wxEvtHandler *parent);
    void e_CameraEnd(wxEvtHandler *parent);

    void e_CalibrationStart(wxEvtHandler *parent);
    void e_CalibrationEnd(wxEvtHandler *parent);

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ChangeToManualPanel(wxEvtHandler *parent);

    void e_ChangeToColorPanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_CALIBRATION;
    std::shared_ptr<SharedModel> shared;

  private:
    void checkPreCondition();

    void startCaptureHandler(wxEvtHandler *parent);
    void endCaptureHandler();

    void startCalibrationHandler(wxEvtHandler *parent);
    void endCalibrationHandler();

    void setPointHandler(wxEvtHandler *parent, cv::Point point);
};