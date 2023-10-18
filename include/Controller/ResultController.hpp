#pragma once

#include <Controller/BaseController.hpp>

#include <Utils/Algorithm/AlgorithmFactory.hpp>

#define RSCPtr std::shared_ptr<ResultController>

/**
 * @brief Controller for ResultPanel
 *
 */
class ResultController : public BaseController {
  public:
    ResultController(ResourcePtr shared);
    ~ResultController();

    void e_ProcessEnd(wxEvtHandler *parent);

    void e_CancelButtonHandler(wxEvtHandler *parent);

    void e_ProcessOFStart(wxEvtHandler *parent);
    void e_ProcessOFEnd(wxEvtHandler *parent);

    void e_ProcessLaneOFStart(wxEvtHandler *parent);
    void e_ProcessLaneOFEnd(wxEvtHandler *parent);

    void e_ProcessDistOFStart(wxEvtHandler *parent);
    void e_ProcessDistOFEnd(wxEvtHandler *parent);

    void e_ProcessCSRTStart(wxEvtHandler *parent);
    void e_ProcessCSRTEnd(wxEvtHandler *parent);

    void e_ProcessLaneCSRTStart(wxEvtHandler *parent);
    void e_ProcessLaneCSRTEnd(wxEvtHandler *parent);

    void e_ProcessDistCSRTStart(wxEvtHandler *parent);
    void e_ProcessDistCSRTEnd(wxEvtHandler *parent);

    void e_ResultPreviewStart(wxEvtHandler *parent);
    void e_ResultPreviewEnd(wxEvtHandler *parent);

    void e_UpdateSpeedPanel(wxEvtHandler *parent);

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

    void processOFStartHandler(wxEvtHandler *parent);
    void processCSRTStartHandler(wxEvtHandler *parent);

    void processLaneOFStartHandler(wxEvtHandler *parent);
    void processLaneCSRTStartHandler(wxEvtHandler *parent);
    void processDistOFStartHandler(wxEvtHandler *parent);
    void processDistCSRTStartHandler(wxEvtHandler *parent);
    void processThreadEndHandler(wxEvtHandler *parent);

    void resultPreviewStartHandler(wxEvtHandler *parent);
    void resultPreviewEndHandler(wxEvtHandler *parent);

    void toggleShowBoxHandler(wxEvtHandler *parent, bool show);
    void toggleShowLanesHandler(wxEvtHandler *parent, bool show);
    void toggleShowLinesHandler(wxEvtHandler *parent, bool show);
    void setIndexToZeroHandler(wxEvtHandler *parent);

    void updateSpeedPanelHandler(wxEvtHandler *parent);

    void processEndHandler(wxEvtHandler *parent);
};