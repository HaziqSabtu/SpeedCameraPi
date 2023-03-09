#include <Event/Event_ProcessImage.hpp>

wxDEFINE_EVENT(c_PROCESS_IMAGE_EVENT, ProcessImageEvent);

ProcessImageEvent::ProcessImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

ProcessImageEvent::ProcessImageEvent(const ProcessImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

wxEvent *ProcessImageEvent::Clone() const {
    return new ProcessImageEvent(*this);
}

// * is cloning necessary? since the image will be cloned by BitMap
void ProcessImageEvent::SetImageData(const cv::Mat &image) {
    m_imageData = image;
}

cv::Mat ProcessImageEvent::GetImageData() const { return m_imageData; }
