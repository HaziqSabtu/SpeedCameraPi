
#include <Event/Event_UpdatePreview.hpp>

wxDEFINE_EVENT(c_UPDATE_PREVIEW_EVENT, UpdatePreviewEvent);

UpdatePreviewEvent::UpdatePreviewEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdatePreviewEvent::UpdatePreviewEvent(const UpdatePreviewEvent& e)
    : wxCommandEvent(e) {
    this->SetImage(e.GetImage());
}

wxEvent* UpdatePreviewEvent::Clone() const {
    return new UpdatePreviewEvent(*this);
}

void UpdatePreviewEvent::SetImage(const wxBitmap& image) {
    this->image = image;
}

void UpdatePreviewEvent::SetImage(const cv::Mat& cvImage) {
    wxBitmap bitmap = wxBitmap(cvImage.cols, cvImage.rows, 24);
    Utils::cvMatToWxBitmap(cvImage, bitmap);
    this->image = bitmap;
}

wxBitmap UpdatePreviewEvent::GetImage() const { return image; }
