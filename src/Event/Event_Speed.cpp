#include <Event/Event_Speed.hpp>

wxDEFINE_EVENT(c_SPEED_CALC_EVENT, SpeedCalcEvent);

SpeedCalcEvent::SpeedCalcEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

SpeedCalcEvent::SpeedCalcEvent(const SpeedCalcEvent &e) : wxCommandEvent(e) {
    this->SetSpeed(e.GetSpeed());
}

wxEvent *SpeedCalcEvent::Clone() const { return new SpeedCalcEvent(*this); }

void SpeedCalcEvent::SetSpeed(const double spd) { this->speed = spd; }

double SpeedCalcEvent::GetSpeed() const { return speed; }
