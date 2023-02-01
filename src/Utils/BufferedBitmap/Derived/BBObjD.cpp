#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>

BBObjD::BBObjD(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBObjD::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();
    cv::Mat img_cp = img.clone();

    if (isBBox) {
        cv::rectangle(img_cp, rect, cv::Scalar(0, 0, 255), 4);
    }

    if (isOptF) {
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

    if (isBotL) {
        cv::line(img_cp, botL[0], botL[1], cv::Scalar(0, 255, 0), 4);
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

bool BBObjD::GetIsBBox() { return isBBox; }

bool BBObjD::GetIsOptF() { return isOptF; }

bool BBObjD::GetIsBotL() { return isBotL; }

void BBObjD::SetRect(cv::Rect r) {
    rect = r;
    Refresh();
}

void BBObjD::setPoints(std::vector<std::vector<cv::Point2f>> p) {
    points = p;
    Refresh();
}

void BBObjD::setBotL(std::vector<cv::Point2f> p) {
    botL = p;
    Refresh();
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBObjD, BufferedBitmap)
EVT_PAINT(BBObjD::OnPaint) 
wxEND_EVENT_TABLE()