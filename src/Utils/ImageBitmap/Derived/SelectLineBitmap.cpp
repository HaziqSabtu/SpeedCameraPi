#include <Utils/ImageBitmap/Derived/SelectLineBitmap.hpp>

SelectLineBitmap::SelectLineBitmap(wxWindow *parent, wxWindowID id,
                                   const wxBitmap &bitmap, const wxPoint &pos,
                                   const wxSize &size, long style,
                                   const wxString &name)
    : ImageBitmap(parent, id, bitmap, pos, size, style, name) {}

void SelectLineBitmap::SetPoints(std::vector<cv::Point2f> *ptns) {
    this->ptns = ptns;
}

void SelectLineBitmap::SetHoughLines(std::vector<cv::Vec4i> *houghLines) {
    this->houghLines = houghLines;
}

void SelectLineBitmap::setSelectedLines(std::vector<cv::Vec4i> *selectedLines) {
    this->selectedLines = selectedLines;
}

SelectLineBitmap::~SelectLineBitmap() {}

void SelectLineBitmap::drawBitMap() {
    if (image.empty()) {
        return;
    }
    processRatio();
    cv::Mat img_cp = image.clone();
    if (ptns != NULL && !ptns->empty()) {
        for (auto p : *ptns) {
            cv::circle(img_cp, p, 3, cv::Scalar(0, 0, 255), -1);
        }
    }

    if (houghLines && !houghLines->empty()) {
        for (auto l : *houghLines) {
            cv::line(img_cp, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                     cv::Scalar(0, 255, 0), 2);
        }
    }

    if (selectedLines && !selectedLines->empty()) {
        for (auto l : *selectedLines) {
            cv::line(img_cp, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                     cv::Scalar(0, 255, 255), 2);
        }
    }
    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

// clang-format off
wxBEGIN_EVENT_TABLE(SelectLineBitmap, ImageBitmap) 
wxEND_EVENT_TABLE()