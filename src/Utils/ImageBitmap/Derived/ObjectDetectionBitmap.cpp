#include <Utils/ImageBitmap/Derived/ObjectDetectionBitmap.hpp>

ObjectDetectionBitmap::ObjectDetectionBitmap(wxWindow *parent, wxWindowID id,
                                             const wxBitmap &bitmap,
                                             const wxPoint &pos,
                                             const wxSize &size, long style,
                                             const wxString &name)
    : ImageBitmap(parent, id, bitmap, pos, size, style, name) {}

ObjectDetectionBitmap::~ObjectDetectionBitmap() {}

void ObjectDetectionBitmap::drawBitMap() {
    if (image.empty()) {
        return;
    }
    processRatio();
    cv::Mat img_cp = image.clone();

    if (bbox) {
        cv::rectangle(img_cp, *bbox, cv::Scalar(0, 0, 255), 2);
    }

    if (result && !result->empty()) {
        for (auto pts : *result) {
            for (auto pt : pts) {
                cv::circle(img_cp, pt, 2, cv::Scalar(255, 255, 0), 2);
            }
        }
    }

    if (bottomLine && bottomLine->size() == 2) {
        cv::Point2f leftPoint = bottomLine->at(0);
        cv::Point2f rightPoint = bottomLine->at(1);
        cv::line(img_cp, leftPoint, rightPoint, cv::Scalar(0, 255, 0), 2);
    }

    if (!selectedLines.empty()) {
        for (auto line : selectedLines) {
            cv::Point2f p1(line[0], line[1]);
            cv::Point2f p2(line[2], line[3]);
            cv::line(img_cp, p1, p2, cv::Scalar(0, 255, 255), 2);
        }
    }

    if (speed && *speed > 0) {
        std::string speedStr = "Speed: " + std::to_string(*speed) + " m/s";
        cv::putText(img_cp, speedStr, cv::Point(10, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

void ObjectDetectionBitmap::SetBBox(cv::Rect *bbox) { this->bbox = bbox; }

void ObjectDetectionBitmap::SetResult(
    std::vector<std::vector<cv::Point2f>> *result) {
    this->result = result;
}

void ObjectDetectionBitmap::SetBottomLine(
    std::vector<cv::Point2f> *bottomLine) {
    this->bottomLine = bottomLine;
}

void ObjectDetectionBitmap::SetSelectedLines(
    std::vector<cv::Vec4i> selectedLines) {
    this->selectedLines = selectedLines;
}

void ObjectDetectionBitmap::SetSpeed(double *speed) { this->speed = speed; }

BEGIN_EVENT_TABLE(ObjectDetectionBitmap, ImageBitmap)
END_EVENT_TABLE()