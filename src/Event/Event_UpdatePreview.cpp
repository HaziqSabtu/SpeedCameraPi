
#include <Event/Event_UpdatePreview.hpp>
#include <opencv2/imgproc.hpp>

wxDEFINE_EVENT(c_UPDATE_PREVIEW_EVENT, UpdatePreviewEvent);

UpdatePreviewEvent::UpdatePreviewEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdatePreviewEvent::UpdatePreviewEvent(const UpdatePreviewEvent &e)
    : wxCommandEvent(e) {
    this->SetImage(e.GetImage());
}

wxEvent *UpdatePreviewEvent::Clone() const {
    return new UpdatePreviewEvent(*this);
}

void UpdatePreviewEvent::SetImage(const wxBitmap &image) {
    this->image = image;
}

void UpdatePreviewEvent::SetImage(const cv::Mat &cvImage) {
    wxBitmap bitmap = wxBitmap(cvImage.cols, cvImage.rows, 24);
    if (cvImage.type() == CV_8UC3) {
        Utils::cvMatToWxBitmap(cvImage, bitmap);
        this->image = bitmap;
        return;
    }
    cv::Mat gray3C;
    cv::cvtColor(cvImage, gray3C, cv::COLOR_GRAY2BGR);
    Utils::cvMatToWxBitmap(gray3C, bitmap);
    this->image = bitmap;
}

wxBitmap UpdatePreviewEvent::GetImage() const { return image; }

void UpdatePreviewEvent::Submit(wxEvtHandler *handler, const wxBitmap &image,
                                int id) {
    UpdatePreviewEvent event(c_UPDATE_PREVIEW_EVENT, id);
    event.SetImage(image);
    wxPostEvent(handler, event);
}

void UpdatePreviewEvent::Submit(wxEvtHandler *handler, const cv::Mat &cvImage,
                                int id) {
    UpdatePreviewEvent event(c_UPDATE_PREVIEW_EVENT, id);
    event.SetImage(cvImage);
    wxPostEvent(handler, event);
}

void UpdatePreviewEvent::Submit(wxEvtHandler *handler, int id) {
    UpdatePreviewEvent event(c_UPDATE_PREVIEW_EVENT, id);
    wxPostEvent(handler, event);
}
