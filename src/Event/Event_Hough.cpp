#include <Event/Event_Hough.hpp>

wxDEFINE_EVENT(c_HOUGH_EVENT, HoughEvent);

HoughEvent::HoughEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

HoughEvent::HoughEvent(const HoughEvent &e) : wxCommandEvent(e) {
    this->SetImageData(e.GetHoughData());
}

wxEvent *HoughEvent::Clone() const { return new HoughEvent(*this); }

void HoughEvent::SetImageData(Detection::HoughData *houghData) {
    this->houghData = houghData;
}

Detection::HoughData *HoughEvent::GetHoughData() const { return houghData; }
