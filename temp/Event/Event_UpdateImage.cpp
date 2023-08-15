
wxDEFINE_EVENT(c_UPDATE_IMAGE_EVENT, UpdateImageEvent);

UpdateImageEvent::UpdateImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdateImageEvent::UpdateImageEvent(const UpdateImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImage());
}

wxEvent *UpdateImageEvent::Clone() const { return new UpdateImageEvent(*this); }

// * is cloning necessary? since the image will be cloned by BitMap
void UpdateImageEvent::SetImageData(const cv::Mat &img) { this->image = img; }

cv::Mat UpdateImageEvent::GetImage() const { return image; }
