#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>

BBObjD::BBObjD(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBObjD::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();
    cv::Mat img_cp = img.clone();

    if (isBBox && rect.width > 0 && rect.height > 0) {
        cv::rectangle(img_cp, rect, cv::Scalar(0, 0, 255), 4);
    }

    if (isOptF && points.size() > 0) {
        if (points.size() == 1) {
            for (auto &p : points[0]) {
                cv::line(img_cp, p, p, cv::Scalar(255, 0, 0), 4);
            }
        } else {
            for (int i = 0; i < points.size() - 1; i++) {
                for (int j = 0; j < points[i].size(); j++) {
                    cv::line(img_cp, points[i][j], points[i + 1][j],
                             cv::Scalar(255, 0, 0), 4);
                }
            }
        }
    }

    if (isBotL && botL.size() > 0) {
        cv::line(img_cp, botL[0], botL[1], cv::Scalar(0, 255, 0), 4);
    }

    if (isLine && line.size() > 0) {
        for (auto &l : line) {
            cv::line(img_cp, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                     cv::Scalar(0, 255, 255), 4);
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

void BBObjD::toggleBBox() {
    isBBox = !isBBox;
    Refresh();
}

void BBObjD::toggleOptF() {
    isOptF = !isOptF;
    Refresh();
}

void BBObjD::toggleBotL() {
    isBotL = !isBotL;
    Refresh();
}

void BBObjD::toggleLine() {
    isLine = !isLine;
    Refresh();
}

bool BBObjD::GetIsBBox() { return isBBox; }

bool BBObjD::GetIsOptF() { return isOptF; }

bool BBObjD::GetIsBotL() { return isBotL; }

bool BBObjD::GetIsLine() { return isLine; }

void BBObjD::SetRect(cv::Rect r) {
    rect = r;
    Refresh();
}

void BBObjD::SetPoints(std::vector<std::vector<cv::Point2f>> p) {
    points = p;
    Refresh();
}

void BBObjD::SetBotL(std::vector<cv::Point2f> p) {
    botL = p;
    Refresh();
}

void BBObjD::SetLine(std::vector<cv::Vec4i> l) {
    line = l;
    Refresh();
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBObjD, BufferedBitmap)
EVT_PAINT(BBObjD::OnPaint) 
wxEND_EVENT_TABLE()