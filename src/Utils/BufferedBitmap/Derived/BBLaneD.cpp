#include <Utils/BufferedBitmap/Derived/BBLaneD.hpp>

BBLaneD::BBLaneD(wxWindow *parent, wxWindowID id, wxSize size)
    : BufferedBitmap(parent, id), DEFAULT_IMG_SIZE(size) {
    RECT_WIDTH = DEFAULT_IMG_SIZE.GetWidth() / IMAGE_PER_ROW;
    RECT_HEIGHT =
        DEFAULT_IMG_SIZE.GetHeight() / (IMAGE_TO_GENERATE / IMAGE_PER_ROW);
}

void BBLaneD::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();
    cv::Mat img_cp = img.clone();
    if (isDrawRect && rectangle.width > 0 && rectangle.height > 0) {
        cv::rectangle(img_cp, rectangle, cv::Scalar(0, 255, 0), 2);
    }

    wxAutoBufferedPaintDC dc(this);

    dc.Clear();

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BBLaneD::RefreshBitmap() { Refresh(); }

void BBLaneD::OnLeftDown(wxMouseEvent &e) {
    isDrawRect = true;

    // determine which area of image is selected
    wxPoint p = e.GetPosition();

    // todo make constant
    int imgpercol = ceil(IMAGE_TO_GENERATE / IMAGE_PER_ROW);

    // int col = 0;
    // int row = 0;
    // while ((col + 1) * BufferedBitmap::width / imgpercol < p.x) {
    //     col++;
    // }

    // while ((row + 1) * BufferedBitmap::height / IMAGE_PER_ROW < p.y) {
    //     row++;
    // }

    int col = p.x / (BufferedBitmap::resizeWidth / imgpercol);
    int row = p.y / (BufferedBitmap::resizeHeight / IMAGE_PER_ROW);

    rectangle =
        cv::Rect(col * RECT_WIDTH, row * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT);
    Refresh();
    e.Skip();
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBLaneD, BufferedBitmap)
EVT_PAINT(BBLaneD::OnPaint) 
EVT_LEFT_DOWN(BBLaneD::OnLeftDown)
wxEND_EVENT_TABLE()