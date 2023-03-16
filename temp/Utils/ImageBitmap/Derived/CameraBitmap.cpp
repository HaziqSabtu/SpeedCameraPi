#include <Utils/ImageBitmap/Derived/CameraBitmap.hpp>

CameraBitmap::CameraBitmap(wxWindow *parent, wxWindowID id,
                           const wxBitmap &bitmap, const wxPoint &pos,
                           const wxSize &size, long style, const wxString &name)
    : ImageBitmap(parent, id, bitmap, pos, size, style, name) {}

CameraBitmap::~CameraBitmap() {}

void CameraBitmap::drawBitMap() {
    // std::cout << "drawBitMap" << std::endl;
    if (image.empty()) {
        return;
    }
    // TODO: fix this later
    // std::cout << "drawBitMap2" << std::endl;
    processRatio();
    // std::cout << "drawBitMap3" << std::endl;

    if (width == 0 || height == 0) {
        return;
    }

    // std::cout << "drawBitMap4" << std::endl;

    cv::Mat img_cp = image.clone();

    // if (*isCapturing) {
    //     // draw box around the frame
    //     std::string text = "Capturing";
    //     cv::Scalar color = cv::Scalar(0, 0, 255);
    //     rectangle(img_cp, cv::Point(0, 0),
    //               cv::Point(image.size().width, image.size().height), color,
    //               4);
    //     cv::putText(img_cp, text, cv::Point(10, 30),
    //     cv::FONT_HERSHEY_SIMPLEX,
    //                 1, color, 2);

    // } else if (*isProcessing) {
    //     // draw box around the frame
    //     std::string text = "Processing";
    //     cv::Scalar color = cv::Scalar(0, 255, 0);
    //     rectangle(img_cp, cv::Point(0, 0),
    //               cv::Point(image.size().width, image.size().height), color,
    //               4);
    //     cv::putText(img_cp, text, cv::Point(10, 30),
    //     cv::FONT_HERSHEY_SIMPLEX,
    //                 1, color, 2);
    // }

    // if (ptns != NULL && !ptns->empty()) {
    //     for (auto p : *ptns) {
    //         cv::circle(img_cp, p, 20, cv::Scalar(0, 0, 255), -1);
    //     }
    // }

    // if (!houghLines.empty()) {
    //     for (auto l : houghLines) {
    //         cv::line(img_cp, l.p1, l.p2, cv::Scalar(0, 255, 0), 2);
    //     }
    // }

    // if (selectedLines && !selectedLines->empty()) {
    //     for (auto l : *selectedLines) {
    //         cv::line(img_cp, l.p1, l.p2, cv::Scalar(0, 255, 255), 2);
    //     }
    // }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

void CameraBitmap::SetPoints(std::vector<cv::Point2f> *ptns) {
    this->ptns = ptns;
}

void CameraBitmap::SetIsCapturing(bool *isCapturing) {
    this->isCapturing = isCapturing;
}

void CameraBitmap::SetIsProcessing(bool *isProcessing) {
    this->isProcessing = isProcessing;
}

void CameraBitmap::SetHoughLines(std::vector<Detection::Line> houghLines) {
    this->houghLines = houghLines;
    drawBitMap();
}

void CameraBitmap::setSelectedLines(
    std::vector<Detection::Line> *selectedLines) {
    this->selectedLines = selectedLines;
    drawBitMap();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraBitmap, ImageBitmap) 
wxEND_EVENT_TABLE()