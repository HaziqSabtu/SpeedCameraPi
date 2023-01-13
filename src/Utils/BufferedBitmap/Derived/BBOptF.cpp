#include <Utils/BufferedBitmap/Derived/BBOptF.hpp>

BBOpticalFlow::BBOpticalFlow(wxWindow *parent, wxWindowID id)
    : BufferedBitmap(parent, id) {}

void BBOpticalFlow::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();

    cv::Mat img_rs;
    cv::resize(img, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    cv::Mat img_cp = img_rs.clone();
    if (draw_rect && rectangle.width > 0 && rectangle.height > 0) {
        cv::rectangle(img_cp, rectangle, cv::Scalar(255, 0, 0), 2);
    }
    wxImage wximg = matToWxImage(img_cp);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BBOpticalFlow::SetTrueRect(cv::Rect r) {
    this->trueRectangle = r;
    this->draw_rect = true;
    this->rectangle = cv::Rect(r.x / widthRatio, r.y / heightRatio,
                               r.width / widthRatio, r.height / heightRatio);
    Refresh();
}

cv::Rect BBOpticalFlow::GetTrueRect() { return this->trueRectangle; }

// clang-format off
wxBEGIN_EVENT_TABLE(BBOpticalFlow, BufferedBitmap)
EVT_PAINT(BBOpticalFlow::OnPaint) 
wxEND_EVENT_TABLE()