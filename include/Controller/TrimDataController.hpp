#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Calibration.hpp"
#include "Thread/Thread_Capture.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Event/Event_UpdateStatus.hpp>
#include <Model/SharedModel.hpp>
#include <memory>
#include <wx/event.h>
#include <wx/thread.h>

#define TDCPtr std::unique_ptr<TrimDataController>

class TrimDataController {
  public:
    TrimDataController(ModelPtr sharedModel);
    ~TrimDataController();

    void e_UpdateState(wxEvtHandler *parent);

    void e_PanelShow(wxEvtHandler *parent);

    void e_CreateTempSessionData(wxEvtHandler *parent);
    void e_RestoreSessionData(wxEvtHandler *parent);
    void e_SaveSessionData(wxEvtHandler *parent);

    void e_OKButtonHandler(wxEvtHandler *parent);
    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_TrimDataStart(wxEvtHandler *parent);
    void e_TrimDataEnd(wxEvtHandler *parent);

    void e_ReplayStart(wxEvtHandler *parent);
    void e_ReplayEnd(wxEvtHandler *parent);

    void e_IncrementStartPos(wxEvtHandler *parent);
    void e_DecrementStartPos(wxEvtHandler *parent);

    void e_IncrementEndPos(wxEvtHandler *parent);
    void e_DecrementEndPos(wxEvtHandler *parent);

    void e_PreviewCurrentRange(wxEvtHandler *parent);

    void e_RestoreDefault(wxEvtHandler *parent);

  private:
    static const PanelID panelID = PanelID::PANEL_TRIM_DATA;
    ModelPtr shared;

  private:
    void checkPreCondition();

    void throwIfAnyThreadIsRunning();

    void killAllThreads(wxEvtHandler *parent);

    void panelShowHandler(wxEvtHandler *parent);

    void okButtonHandler(wxEvtHandler *parent);
    void cancelButtonHandler(wxEvtHandler *parent);

    void createTempSessionDataHandler(wxEvtHandler *parent);
    void restoreSessionDataHandler(wxEvtHandler *parent);
    void saveSessionDataHandler(wxEvtHandler *parent);

    void trimDataStartHandler(wxEvtHandler *parent);
    void trimDataEndHandler(wxEvtHandler *parent);

    void replayStartHandler(wxEvtHandler *parent);
    void replayEndHandler(wxEvtHandler *parent);

    void incrementStartPosHandler(wxEvtHandler *parent);
    void decrementStartPosHandler(wxEvtHandler *parent);

    void incrementEndPosHandler(wxEvtHandler *parent);
    void decrementEndPosHandler(wxEvtHandler *parent);

    void previewCurrentRangeHandler(wxEvtHandler *parent);

    void restoreDefaultHandler(wxEvtHandler *parent);
};