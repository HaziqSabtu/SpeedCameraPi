#include <Event/Event_Hough.hpp>

wxDEFINE_EVENT(c_HOUGH_EVENT, HoughEvent);

HoughEvent::HoughEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

HoughEvent::HoughEvent(const HoughEvent &e) : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

wxEvent *HoughEvent::Clone() const { return new HoughEvent(*this); }

void HoughEvent::SetImageData(std::vector<ImageData> *imgData) {
    this->imgData = imgData;
}

std::vector<ImageData> *HoughEvent::GetImageData() const { return imgData; }
