#include <Utils/BufferedBitmap.hpp>

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
    client_size = GetClientSize();

    int width = client_size.GetWidth();
    int height = client_size.GetHeight();

    imgRatio = (double)img.cols / (double)img.rows;
    clientRatio = (double)width / (double)height;

    if (imgRatio > clientRatio) {
        resizeWidth = width;
        resizeHeight = (int)((double)width / imgRatio);
    } else {
        resizeHeight = height;
        resizeWidth = (int)((double)height * imgRatio);
    }

    widthRatio = (double)img.cols / (double)resizeWidth;
    heightRatio = (double)img.rows / (double)resizeHeight;

    cv::Mat img_rs;
    cv::resize(img, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    cv::Mat img_cp = img_rs.clone();
    // cv::Mat img_cp2 = img.clone();

    if (draw_rect && rectangle.width > 0 && rectangle.height > 0) {
        cv::rectangle(img_cp, rectangle, cv::Scalar(0, 255, 0), 2);
        // cv::rectangle(img_cp2, trueRectangle, cv::Scalar(0, 255, 0), 2);
    }

    // cv::imshow("img", img_cp2);

    // set clinet size to string
    std::string cs = "Client Size: " + std::to_string(client_size.GetWidth()) +
                     "x" + std::to_string(client_size.GetHeight());
    std::string cs2 =
        "Client Size 2: " + std::to_string(client_size2.GetWidth()) + "x" +
        std::to_string(client_size2.GetHeight());
    std::string cs3 = "RatioWidth: " + std::to_string(widthRatio) +
                      "  RatioHeight: " + std::to_string(heightRatio);
    cv::putText(img_cp, cs, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(0, 0, 255), 2);
    // cv::putText(img_cp, cs2, cv::Point(10, 70), cv::FONT_HERSHEY_SIMPLEX, 1,
    //             cv::Scalar(0, 0, 255), 2);
    // cv::putText(img_cp, cs3, cv::Point(10, 110), cv::FONT_HERSHEY_SIMPLEX, 1,
    //             cv::Scalar(0, 0, 255), 2);
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
            trueRectangle =
                cv::Rect(start_x * widthRatio, start_y * heightRatio,
                         (end_x - start_x) * widthRatio,
                         (end_y - start_y) * heightRatio);
        } else if (start_x > end_x && start_y < end_y) {
            rectangle =
                cv::Rect(end_x, start_y, start_x - end_x, end_y - start_y);
            trueRectangle = cv::Rect(end_x * widthRatio, start_y * heightRatio,
                                     (start_x - end_x) * widthRatio,
                                     (end_y - start_y) * heightRatio);
        } else if (start_x < end_x && start_y > end_y) {
            rectangle =
                cv::Rect(start_x, end_y, end_x - start_x, start_y - end_y);
            trueRectangle = cv::Rect(start_x * widthRatio, end_y * heightRatio,
                                     (end_x - start_x) * widthRatio,
                                     (start_y - end_y) * heightRatio);
        } else if (start_x > end_x && start_y > end_y) {
            rectangle =
                cv::Rect(end_x, end_y, start_x - end_x, start_y - end_y);
            trueRectangle = cv::Rect(end_x * widthRatio, end_y * heightRatio,
                                     (start_x - end_x) * widthRatio,
                                     (start_y - end_y) * heightRatio);
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
                trueRectangle =
                    cv::Rect(start_x * widthRatio, start_y * heightRatio,
                             (end_x - start_x) * widthRatio,
                             (end_y - start_y) * heightRatio);
            } else if (start_x > end_x && start_y < end_y) {
                rectangle =
                    cv::Rect(end_x, start_y, start_x - end_x, end_y - start_y);
                trueRectangle =
                    cv::Rect(end_x * widthRatio, start_y * heightRatio,
                             (start_x - end_x) * widthRatio,
                             (end_y - start_y) * heightRatio);
            } else if (start_x < end_x && start_y > end_y) {
                rectangle =
                    cv::Rect(start_x, end_y, end_x - start_x, start_y - end_y);
                trueRectangle =
                    cv::Rect(start_x * widthRatio, end_y * heightRatio,
                             (end_x - start_x) * widthRatio,
                             (start_y - end_y) * heightRatio);
            } else if (start_x > end_x && start_y > end_y) {
                rectangle =
                    cv::Rect(end_x, end_y, start_x - end_x, start_y - end_y);
                trueRectangle =
                    cv::Rect(end_x * widthRatio, end_y * heightRatio,
                             (start_x - end_x) * widthRatio,
                             (start_y - end_y) * heightRatio);
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

void BufferedBitmap::setClientSize(wxSize size) { client_size2 = size; }

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
