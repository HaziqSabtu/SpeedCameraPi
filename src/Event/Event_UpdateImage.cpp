#include <Event/Event_UpdateImage.hpp>

wxDEFINE_EVENT(c_UPDATE_IMAGE_EVENT, UpdateImageEvent);

UpdateImageEvent::UpdateImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdateImageEvent::UpdateImageEvent(const UpdateImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

wxEvent *UpdateImageEvent::Clone() const { return new UpdateImageEvent(*this); }

void UpdateImageEvent::SetImageData(const ImageData &imgData) {
    this->imgData = imgData;
}

ImageData UpdateImageEvent::GetImageData() const { return imgData; }
