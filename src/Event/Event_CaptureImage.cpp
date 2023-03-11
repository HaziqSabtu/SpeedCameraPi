#include <Event/Event_CaptureImage.hpp>

wxDEFINE_EVENT(c_CAPTURE_IMAGE_EVENT, CaptureImageEvent);

CaptureImageEvent::CaptureImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

CaptureImageEvent::CaptureImageEvent(const CaptureImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

wxEvent *CaptureImageEvent::Clone() const {
    return new CaptureImageEvent(*this);
}

void CaptureImageEvent::SetImageData(std::vector<ImageData> *imgData) {
    this->imgData = imgData;
}

std::vector<ImageData> *CaptureImageEvent::GetImageData() const {
    return imgData;
}
