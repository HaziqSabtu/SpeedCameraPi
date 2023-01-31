#include <Utils/BufferedBitmap/Derived/BBLane.hpp>

BBLane::BBLane(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBLane::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();
    cv::Mat img_cp = img.clone();
    if (isHough) {
        if (linesP.empty()) {
            wxLogMessage("[ERROR] linesP is empty");
        } else {
            for (auto &line : linesP) {
                cv::line(img_cp, cv::Point(line[0], line[1]),
                         cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 3,
                         cv::LINE_AA);
            }
        }
    }

    if (!detLines.empty()) {
        for (auto &line : detLines) {
            cv::line(img_cp, cv::Point(line[0], line[1]),
                     cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0), 3,
                     cv::LINE_AA);
        }
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    wxImage wximg = matToWxImage(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BBLane::SetLinesP(const std::vector<cv::Vec4i> &linesP) {
    this->linesP = linesP;
}

void BBLane::ToggleHough() {
    isHough = !isHough;
    Refresh();
}

void BBLane::addLine(cv::Vec4i line) {
    if (detLines.size() <= 1) {
        detLines.push_back(line);
    } else {
        detLines[1] = line;
    }
    Refresh();
}

void BBLane::clearLines() {
    detLines.clear();
    Refresh();
}

bool BBLane::GetIsHough() { return isHough; }

wxPoint BBLane::GetRealMousePos(wxPoint mousePos) {
    wxPoint realMousePos;
    realMousePos.x = mousePos.x * widthRatio;
    realMousePos.y = mousePos.y * heightRatio;
    return realMousePos;
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBLane, BufferedBitmap)
EVT_PAINT(BBLane::OnPaint)
wxEND_EVENT_TABLE()

