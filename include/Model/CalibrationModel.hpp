#pragma once

#include "Model/SessionData.hpp"
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

    void e_ToggleCamera(wxEvtHandler *parent, bool state);

    void e_ChangePanel(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_CALIBRATION;

    std::shared_ptr<SharedModel> shared;

    wxThread *captureThread;

    void initThreads();
    void deleteThreads();

    void checkPreCondition();

    void startCaptureHandler(wxEvtHandler *parent);

    virtual wxThread *initCaptureThread(wxEvtHandler *parent,
                                        std::shared_ptr<CameraBase> camera);
    void endCaptureHandler();

    void switchPanelHandler(wxEvtHandler *parent);
    virtual bool isRequirementFulfilled();

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);
};