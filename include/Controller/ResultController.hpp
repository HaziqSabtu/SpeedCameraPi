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

#define RSCPtr std::unique_ptr<ResultController>

class ResultController {
  public:
    ResultController(ModelPtr sharedModel);
    ~ResultController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_ChangeToCapturePanel(wxEvtHandler *parent);

    void e_ProcessThreadStart(wxEvtHandler *parent);
    void e_ProcessThreadEnd(wxEvtHandler *parent);

    void e_ResultPreviewStart(wxEvtHandler *parent);
    void e_ResultPreviewEnd(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_RESULT;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void processThreadStartHandler(wxEvtHandler *parent);
    void processThreadEndHandler(wxEvtHandler *parent);

    void resultPreviewStartHandler(wxEvtHandler *parent);
    void resultPreviewEndHandler(wxEvtHandler *parent);
};