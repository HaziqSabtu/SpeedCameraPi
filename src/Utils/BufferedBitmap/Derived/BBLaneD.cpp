#include <Utils/BufferedBitmap/Derived/BBLaneD.hpp>

BBLaneD::BBLaneD(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBLaneD::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();

    cv::Mat img_rs;
    cv::resize(img, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);
    // wxPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    // cv::Mat img_cp = img_rs.clone();

    wxImage wximg = matToWxImage(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BBLaneD::RefreshBitmap() { Refresh(); }

// clang-format off
wxBEGIN_EVENT_TABLE(BBLaneD, BufferedBitmap)
EVT_PAINT(BBLaneD::OnPaint) 
wxEND_EVENT_TABLE()