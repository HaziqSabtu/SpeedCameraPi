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
        std::string text = "Capturing";
        cv::Scalar color = cv::Scalar(0, 0, 255);
        rectangle(img_cp, cv::Point(0, 0),
                  cv::Point(image.size().width, image.size().height), color, 4);
        cv::putText(img_cp, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX,
                    1, color, 2);

    } else if (*isProcessing) {
        // draw box around the frame
        std::string text = "Processing";
        cv::Scalar color = cv::Scalar(0, 255, 0);
        rectangle(img_cp, cv::Point(0, 0),
                  cv::Point(image.size().width, image.size().height), color, 4);
        cv::putText(img_cp, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX,
                    1, color, 2);
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

void CameraBitmap::SetIsCapturing(bool *isCapturing) {
    this->isCapturing = isCapturing;
}

void CameraBitmap::SetIsProcessing(bool *isProcessing) {
    this->isProcessing = isProcessing;
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraBitmap, ImageBitmap) 
wxEND_EVENT_TABLE()