#include "Model/AppState.hpp"
#include <Event/Event_UpdateState.hpp>

wxDEFINE_EVENT(c_UPDATE_STATE_EVENT, UpdateStateEvent);

UpdateStateEvent::UpdateStateEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdateStateEvent::UpdateStateEvent(const UpdateStateEvent &e)
    : wxCommandEvent(e) {
    this->SetState(e.GetState());
}

wxEvent *UpdateStateEvent::Clone() const { return new UpdateStateEvent(*this); }

void UpdateStateEvent::SetState(const AppState &state) { this->state = state; }

AppState UpdateStateEvent::GetState() const { return this->state; }

void UpdateStateEvent::Submit(wxEvtHandler *handler, const AppState &state,
                              int id) {
    UpdateStateEvent event(c_UPDATE_STATE_EVENT, UPDATE_STATE);
    event.SetState(state);
    wxPostEvent(handler, event);
}