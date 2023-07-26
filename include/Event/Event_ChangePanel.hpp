#pragma once

#include "Model/SessionData.hpp"
#include <wx/event.h>

class ChangePanelEvent;
wxDECLARE_EVENT(c_CHANGE_PANEL_EVENT, ChangePanelEvent);

enum CHANGE_PANEL_EVENT_TYPE { CHANGE_OK = 1, CHANGE_ERROR };

struct ChangePanelData {
    PanelID currentPanelID;
    PanelID nextPanelID;

    ChangePanelData() : currentPanelID(PANEL_NONE), nextPanelID(PANEL_NONE) {}

    ChangePanelData(PanelID currentPanelID, PanelID nextPanelID)
        : currentPanelID(currentPanelID), nextPanelID(nextPanelID) {}
};

class ChangePanelEvent : public wxCommandEvent {
  public:
    static void Submit(wxEvtHandler *parent, ChangePanelData data, int id = 1);

  public:
    ChangePanelEvent(wxEventType eventType = c_CHANGE_PANEL_EVENT, int id = 1);
    ChangePanelEvent(const ChangePanelEvent &e);
    virtual wxEvent *Clone() const;

    void SetPanelData(const ChangePanelData &data);

    ChangePanelData GetPanelData() const;

  private:
    ChangePanelData panelData;
};

typedef void (wxEvtHandler::*ChangePanelFunction)(ChangePanelEvent &);
#define ChangePanelHandler(func) wxEVENT_HANDLER_CAST(ChangePanelFunction, func)
#define EVT_CHANGEPANEL(id, func)                                              \
    wx__DECLARE_EVT1(c_CHANGE_PANEL_EVENT, id, ChangePanelHandler(func))
