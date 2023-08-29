#pragma once

#include <Controller/BaseController.hpp>

#include <Event/Event_UpdateState.hpp>

#include <Model/SessionData.hpp>
#include <Model/SharedModel.hpp>

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_ResultPreview.hpp>

#include <Utils/Camera/CameraBase.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Config/ConfigStruct.hpp>
#include <Utils/wxUtils.hpp>

#include <memory>
#include <vector>

#include <wx/event.h>
#include <wx/object.h>
#include <wx/thread.h>

#define RSCPtr std::shared_ptr<ResultController>

class ResultController : public BaseController {
  public:
    ResultController(ModelPtr sharedModel);
    ~ResultController();

    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_ProcessThreadStart(wxEvtHandler *parent);
    void e_ProcessThreadEnd(wxEvtHandler *parent);

    void e_ResultPreviewStart(wxEvtHandler *parent);
    void e_ResultPreviewEnd(wxEvtHandler *parent);

    void e_ToggleShowBox(wxEvtHandler *parent, bool show);
    void e_ToggleShowLanes(wxEvtHandler *parent, bool show);
    void e_ToggleShowLines(wxEvtHandler *parent, bool show);
    void e_SetIndexToZero(wxEvtHandler *parent);

  private:
    static const PanelID currentPanelID = PanelID::PANEL_RESULT;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

    void panelShowHandler(wxEvtHandler *parent) override;
    void okButtonHandler(wxEvtHandler *parent) override;
    void cancelButtonHandler(wxEvtHandler *parent) override;

    void processThreadStartHandler(wxEvtHandler *parent);
    void processThreadEndHandler(wxEvtHandler *parent);

    void resultPreviewStartHandler(wxEvtHandler *parent);
    void resultPreviewEndHandler(wxEvtHandler *parent);

    void toggleShowBoxHandler(wxEvtHandler *parent, bool show);
    void toggleShowLanesHandler(wxEvtHandler *parent, bool show);
    void toggleShowLinesHandler(wxEvtHandler *parent, bool show);
    void setIndexToZeroHandler(wxEvtHandler *parent);
};