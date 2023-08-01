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

#define ROCPtr std::unique_ptr<RoiController>

class RoiController {
  public:
    RoiController(ModelPtr sharedModel);
    ~RoiController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ClearRect(wxEvtHandler *parent);

    void e_SetPoint1(wxEvtHandler *parent, wxPoint point);
    void e_SetPoint2(wxEvtHandler *parent, wxPoint point);

    void e_RoiThreadStart(wxEvtHandler *parent);
    void e_RoiThreadEnd(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_ROI;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void clearRectHandler(wxEvtHandler *parent);

    void setPoint1Handler(wxEvtHandler *parent, cv::Point point);
    void setPoint2Handler(wxEvtHandler *parent, cv::Point point);

    void roiThreadStartHandler(wxEvtHandler *parent);
    void roiThreadEndHandler(wxEvtHandler *parent);
};