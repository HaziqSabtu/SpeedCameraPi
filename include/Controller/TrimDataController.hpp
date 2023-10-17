#pragma once

#include <Controller/BaseController.hpp>

#define TDCPtr std::shared_ptr<TrimDataController>

class TrimDataController : public BaseController {
  public:
    TrimDataController(ModelPtr sharedModel);
    ~TrimDataController();

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
    static const PanelID currentPanelID = PanelID::PANEL_TRIM_DATA;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

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