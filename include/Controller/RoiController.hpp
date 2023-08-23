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

#define ROCPtr std::unique_ptr<RoiController>

class RoiController {
  public:
    RoiController(ModelPtr sharedModel);
    ~RoiController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_PanelShow(wxEvtHandler *parent);

    void e_CreateTempSessionData(wxEvtHandler *parent);
    void e_RestoreSessionData(wxEvtHandler *parent);
    void e_SaveSessionData(wxEvtHandler *parent);

    void e_OKButtonHandler(wxEvtHandler *parent);
    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_ClearRect(wxEvtHandler *parent);
    void e_RemoveRect(wxEvtHandler *parent);

    void e_SetPoint1(wxEvtHandler *parent, wxPoint point);
    void e_SetPoint2(wxEvtHandler *parent, wxPoint point);
    void e_SaveRect(wxEvtHandler *parent, wxPoint point);

    void e_RoiThreadStart(wxEvtHandler *parent);
    void e_RoiThreadSave(wxEvtHandler *parent);
    void e_RoiThreadCancel(wxEvtHandler *parent);

    void e_RoiPreviewStart(wxEvtHandler *parent);
    void e_RoiPreviewEnd(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_ROI;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void throwIfAnyThreadIsRunning();

    void killAllThreads(wxEvtHandler *parent);

    void clearRectHandler(wxEvtHandler *parent);
    void removeRectHandler(wxEvtHandler *parent);

    void okButtonHandler(wxEvtHandler *parent);
    void cancelButtonHandler(wxEvtHandler *parent);

    void setPoint1Handler(wxEvtHandler *parent, cv::Point point);
    void setPoint2Handler(wxEvtHandler *parent, cv::Point point);
    void saveRectHandler(wxEvtHandler *parent, cv::Point point);

    void roiThreadStartHandler(wxEvtHandler *parent);
    void roiThreadSaveHandler(wxEvtHandler *parent);
    void roiThreadCancelHandler(wxEvtHandler *parent);

    void roiPreviewStartHandler(wxEvtHandler *parent);
    void roiPreviewEndHandler(wxEvtHandler *parent);

    void createTempSessionDataHandler(wxEvtHandler *parent);
    void restoreSessionDataHandler(wxEvtHandler *parent);
    void saveSessionDataHandler(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent);
};