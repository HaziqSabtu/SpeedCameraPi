#include "BufferedBitmap.hpp"

BufferedBitmap::BufferedBitmap(wxWindow *parent, wxWindowID id)
    : wxStaticBitmap(parent, id, wxNullBitmap) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BufferedBitmap::SetImage(const cv::Mat &image) {
    img = image.clone();
    wxImage wximg = matToWxImage(img);
    wxStaticBitmap::SetBitmap(wxBitmap(wximg));
}

void BufferedBitmap::OnPaint(wxPaintEvent &event) {
    wxAutoBufferedPaintDC dc(this);
    cv::Mat img_cp = img.clone();
    if (draw_rect && rectangle.width > 0 && rectangle.height > 0) {
        cv::rectangle(img_cp, rectangle, cv::Scalar(0, 255, 0), 2);
    }
    wxImage wximg = matToWxImage(img_cp);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BufferedBitmap::OnLeftDown(wxMouseEvent &event) {
    draw_rect = true;
    start_x = event.GetX();
    start_y = event.GetY();
}

void BufferedBitmap::OnLeftUp(wxMouseEvent &event) {
    end_x = event.GetX();
    end_y = event.GetY();
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
        Refresh();
    }
    // draw_rect = false;
}

void BufferedBitmap::OnMouseMove(wxMouseEvent &e) {
    if (e.Dragging() && e.LeftIsDown()) {
        end_x = e.GetX();
        end_y = e.GetY();
        if (start_x != -1 && start_y != -1 && end_x != -1 && end_y != -1) {
            if (start_x < end_x && start_y < end_y) {
                rectangle = cv::Rect(start_x, start_y, end_x - start_x,
                                     end_y - start_y);
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
            Refresh();
        }
    }
}

void BufferedBitmap::DrawRectangle(int x, int y, int width, int height) {
    draw_rect = true;
    rectangle = cv::Rect(x, y, width, height);
}

void BufferedBitmap::DrawRectangle(wxPoint p1, wxPoint p2) {
    draw_rect = true;
    rectangle = cv::Rect(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
}

void BufferedBitmap::RemoveRectangle() {
    draw_rect = false;
    start_x = -1;
    start_y = -1;
    end_x = -1;
    end_y = -1;
    Refresh();
}

wxImage BufferedBitmap::matToWxImage(const cv::Mat &mat) {
    if (mat.empty())
        return wxImage();
    if (mat.type() == CV_8UC3) {
        cv::cvtColor(mat, RGBImg, cv::COLOR_BGR2RGB);
        // cv::imshow("temp", mat);
        wxImage img(RGBImg.cols, RGBImg.rows, RGBImg.data, true);
        return img;

    } else if (mat.type() == CV_8UC1) {
        wxImage image(mat.cols, mat.rows, mat.data);
        return image.ConvertToGreyscale();
    } else
        throw std::runtime_error("Unsupported image format");
}

// clang-format off
wxBEGIN_EVENT_TABLE(BufferedBitmap, wxStaticBitmap)
EVT_PAINT(BufferedBitmap::OnPaint) 
EVT_LEFT_DOWN(BufferedBitmap::OnLeftDown)
EVT_LEFT_UP(BufferedBitmap::OnLeftUp)
EVT_MOTION(BufferedBitmap::OnMouseMove)
wxEND_EVENT_TABLE()
