#include <Utils/BufferedBitmap/Derived/BBObjD.hpp>

BBObjD::BBObjD(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBObjD::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();

    cv::Mat img_rs;
    cv::resize(img, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    wxImage wximg = matToWxImage(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBObjD, BufferedBitmap)
EVT_PAINT(BBObjD::OnPaint) 
wxEND_EVENT_TABLE()