#pragma once

#include "Model/AppState.hpp"
#include <wx/event.h>
#include <wx/string.h>

class UpdateStateEvent;
wxDECLARE_EVENT(c_UPDATE_STATE_EVENT, UpdateStateEvent);

enum UPDATE_STATE_EVENT_TYPE { UPDATE_STATE = 1 };

class UpdateStateEvent : public wxCommandEvent {
  public:
    static void Submit(wxEvtHandler *handler, const AppState &state,
                       int id = 1);

  public:
    UpdateStateEvent(wxEventType eventType = c_UPDATE_STATE_EVENT, int id = 1);
    UpdateStateEvent(const UpdateStateEvent &e);
    virtual wxEvent *Clone() const;

    void SetState(const AppState &state);

    AppState GetState() const;

  private:
    AppState state;
};

typedef void (wxEvtHandler::*UpdateStateFunction)(UpdateStateEvent &);
#define UpdateStateHandler(func) wxEVENT_HANDLER_CAST(UpdateStateFunction, func)
#define EVT_UPDATE_STATE(id, func)                                             \
    wx__DECLARE_EVT1(c_UPDATE_STATE_EVENT, id, UpdateStateHandler(func))
