#include <Utils/ImageBitmap/Derived/CameraBitmap.hpp>

CameraBitmap::CameraBitmap(wxWindow *parent, wxWindowID id,
                           const wxBitmap &bitmap, const wxPoint &pos,
                           const wxSize &size, long style, const wxString &name)
    : ImageBitmap(parent, id, bitmap, pos, size, style, name) {}

CameraBitmap::~CameraBitmap() {}

void CameraBitmap::drawBitMap() {
    if (image.empty()) {
        return;
    }

    // TODO: fix this later
    processRatio();
    if (width == 0 || height == 0) {
        return;
    }

    cv::Mat img_cp = image.clone();

    if (*isCapturing) {
        // draw box around the frame
        rectangle(img_cp, cv::Point(0, 0),
                  cv::Point(image.size().width, image.size().height),
                  cv::Scalar(0, 0, 255), 4);
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

void CameraBitmap::SetIsCapturing(bool *isCapturing) {
    this->isCapturing = isCapturing;
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraBitmap, ImageBitmap) 
wxEND_EVENT_TABLE()