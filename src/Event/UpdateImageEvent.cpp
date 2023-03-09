#include <Event/UpdateImageEvent.hpp>

// wxDECLARE_EVENT(SET_IMAGE_EVENT_TYPE, SetImageEvent);
wxDEFINE_EVENT(SET_IMAGE_EVENT_TYPE, SetImageEvent);

SetImageEvent::SetImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

SetImageEvent::SetImageEvent(const SetImageEvent &e) : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

wxEvent *SetImageEvent::Clone() const { return new SetImageEvent(*this); }

void SetImageEvent::SetImageData(const std::string &image) {
    // clone string to avoid dangling pointer
    m_imageData = image;
    // m_imageData = image.clone();
}

// std::string SetImageEvent::GetImageData() const { return m_imageData.clone();
// }
std::string SetImageEvent::GetImageData() const { return m_imageData; }