#include <Event/Event_UpdateSpeed.hpp>

wxDEFINE_EVENT(c_UPDATE_SPEED_EVENT, UpdateSpeedEvent);

UpdateSpeedEvent::UpdateSpeedEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdateSpeedEvent::UpdateSpeedEvent(const UpdateSpeedEvent &e)
    : wxCommandEvent(e) {
    this->SetSpeed(e.GetSpeed());
}

wxEvent *UpdateSpeedEvent::Clone() const { return new UpdateSpeedEvent(*this); }

void UpdateSpeedEvent::SetSpeed(const double spd) { this->speed = spd; }

double UpdateSpeedEvent::GetSpeed() const { return speed; }

void UpdateSpeedEvent::Submit(wxEvtHandler *handler, const double spd, int id) {
    UpdateSpeedEvent event(c_UPDATE_SPEED_EVENT, id);
    event.SetSpeed(spd);
    wxPostEvent(handler, event);
}
