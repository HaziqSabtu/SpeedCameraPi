#include <Utils/BufferedBitmap/Derived/BBImage.hpp>

BBImage::BBImage(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BBImage::DrawRectangle(int x, int y, int width, int height) {
    draw_rect = true;
    rectangle = cv::Rect(x, y, width, height);
}

void BBImage::RemoveRectangle() {
    draw_rect = false;
    start_x = -1;
    start_y = -1;
    end_x = -1;
    end_y = -1;
    Refresh();
}

void BBImage::OnLeftDown(wxMouseEvent &e) {
    draw_rect = true;
    start_x = e.GetX();
    start_y = e.GetY();
}

void BBImage::processRect() {
    if (start_x != -1 && start_y != -1 && end_x != -1 && end_y != -1) {
        if (start_x < end_x && start_y < end_y) {
            rectangle =
                cv::Rect(start_x, start_y, end_x - start_x, end_y - start_y);
        } else if (start_x > end_x && start_y < end_y) {
            rectangle =
                cv::Rect(end_x, start_y, start_x - end_x, end_y - start_y);
        } else if (start_x < end_x && start_y > end_y) {
            rectangle =
                cv::Rect(start_x, end_y, end_x - start_x, start_y - end_y);
        } else if (start_x > end_x && start_y > end_y) {
            rectangle =
                cv::Rect(end_x, end_y, start_x - end_x, start_y - end_y);
        }
        trueRectangle = cv::Rect(
            rectangle.x * widthRatio, rectangle.y * heightRatio,
            rectangle.width * widthRatio, rectangle.height * heightRatio);
        Refresh();
    }
}

void BBImage::OnLeftUp(wxMouseEvent &e) {
    end_x = e.GetX();
    end_y = e.GetY();

    processRect();
}

void BBImage::OnMouseMove(wxMouseEvent &e) {
    if (e.Dragging() && e.LeftIsDown()) {
        end_x = e.GetX();
        end_y = e.GetY();

        processRect();
    }
}

void BBImage::OnPaint(wxPaintEvent &e) {
    BufferedBitmap::processRatio();

    cv::Mat img_rs;
    cv::resize(img, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    cv::Mat img_cp = img_rs.clone();

    if (draw_rect && rectangle.width > 0 && rectangle.height > 0) {
        cv::rectangle(img_cp, rectangle, cv::Scalar(0, 255, 0), 2);
    }
    wxImage wximg = matToWxImage(img_cp);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

cv::Rect BBImage::GetTrueRect() { return trueRectangle; }

// clang-format off
wxBEGIN_EVENT_TABLE(BBImage, BufferedBitmap)
EVT_PAINT(BBImage::OnPaint) 
EVT_LEFT_DOWN(BBImage::OnLeftDown)
EVT_LEFT_UP(BBImage::OnLeftUp)
EVT_MOTION(BBImage::OnMouseMove)
wxEND_EVENT_TABLE()