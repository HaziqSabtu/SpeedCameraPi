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

    wxImage wximg = matToWxImage(img_cp);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}