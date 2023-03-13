#include <Utils/ImageBitmap/Bit.hpp>

wxImagePanel::wxImagePanel(wxPanel *parent)
    : wxPanel(parent), showType(SHOW_TYPE_IMAGE), isShowHoughLine(false),
      isShowSelectedLine(false), isRect(false), isOFPoint(false),
      isBotLine(false) {
    noImage = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(noImage, "No Image", cv::Point(200, 240),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2,
                cv::LINE_AA);
    // Bind(wxEVT_LEFT_DOWN, &wxImagePanel::OnLeftDown, this);
    w = -1;
    h = -1;
}

void wxImagePanel::OnLeftDown(wxMouseEvent &e) {
    std::cout << "Left Down" << std::endl;
    e.Skip();
}

void wxImagePanel::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void wxImagePanel::SetImageData(ImageData &imgData) {
    this->imgData = imgData;
    paintNow();
}

void wxImagePanel::SetShowHoughLine(bool isl) {
    this->isShowHoughLine = isl;
    paintNow();
}

void wxImagePanel::SetSpeed(double speed) {
    this->speed = speed;
    paintNow();
}

void wxImagePanel::SetImageData() {
    this->showType = SHOW_TYPE_NONE;
    paintNow();
}

void wxImagePanel::SetShowType(SHOW_TYPE showType) {
    this->showType = showType;
    paintNow();
}

void wxImagePanel::SetIsRect(bool isRect) {
    this->isRect = isRect;
    paintNow();
}

void wxImagePanel::SetIsOFPoint(bool isOFPoint) {
    this->isOFPoint = isOFPoint;
    paintNow();
}

void wxImagePanel::SetShowSelectedLine(bool isl) {
    this->isShowSelectedLine = isl;
    paintNow();
}

void wxImagePanel::SetSelectedLine(std::vector<Detection::Line> &selectedLine) {
    this->selectedLine = selectedLine;
    paintNow();
}

void wxImagePanel::SetSelectedPoint(std::vector<cv::Point2f> &selectedPoint) {
    this->selectedPoint = selectedPoint;
    paintNow();
}

void wxImagePanel::SetIsBotLine(bool isBotLine) {
    this->isBotLine = isBotLine;
    paintNow();
}

cv::Point2f wxImagePanel::calcMousePos(wxPoint &mousePos) {
    float x = (float)mousePos.x * widthRatio;
    float y = (float)mousePos.y * heightRatio;
    return cv::Point2f(x, y);
}

void wxImagePanel::calcRatio(wxDC &dc) {
    int newW, newH;
    dc.GetSize(&newW, &newH);
    if (newW == w && newH == h) {
        return;
    }
    w = newW;
    h = newH;
}

void wxImagePanel::render(wxDC &dc) {
    calcRatio(dc);

    switch (showType) {
    case SHOW_TYPE_NONE:
        image = noImage.clone();
        break;
    case SHOW_TYPE_IMAGE:
        image = imgData.image.clone();
        break;
    case SHOW_TYPE_CANNY:
        image = imgData.hough.canny.clone();
        break;
    }

    if (isShowHoughLine && !imgData.hough.lines.empty()) {
        for (auto &line : imgData.hough.lines) {
            cv::line(image, line.p1, line.p2, cv::Scalar(0, 0, 255), 2,
                     cv::LINE_AA);
        }
    }

    if (!selectedPoint.empty()) {
        for (auto &point : selectedPoint) {
            cv::circle(image, point, 5, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
        }
    }

    if (isShowSelectedLine && !selectedLine.empty()) {
        for (auto &line : selectedLine) {
            cv::line(image, line.p1, line.p2, cv::Scalar(0, 255, 0), 2,
                     cv::LINE_AA);
        }
    }

    if (!imgData.detection.points.empty()) {
        if (isRect) {
            cv::Rect rect = imgData.detection.GetRect();
            cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
        }

        if (isOFPoint) {
            for (auto &point : imgData.detection.GetPoints()) {
                cv::circle(image, point, 3, cv::Scalar(255, 0, 0), -1,
                           cv::LINE_AA);
            }
        }

        if (isBotLine && !selectedLine.empty()) {
            Detection::Line l = imgData.detection.GetLine();
            cv::Point2f int1 = l.Intersection(selectedLine[0]);
            cv::Point2f int2 = l.Intersection(selectedLine[1]);
            Detection::Line botLine(int1, int2);
            cv::line(image, botLine.p1, botLine.p2, cv::Scalar(0, 255, 0), 2,
                     cv::LINE_AA);
        }
    }

    if (speed != -1) {
        std::string text = "Speed: " + std::to_string(speed) + " m/s";
        cv::putText(image, text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1,
                    cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    if (image.empty()) {
        image = noImage;
    }

    widthRatio = (float)image.cols / (float)w;
    heightRatio = (float)image.rows / (float)h;

    cv::resize(image, image, cv::Size(w, h));
    resized = wxBitmap(image.cols, image.rows, 24);
    ConvertMatBitmapTowxBitmap(image, resized);
    dc.DrawBitmap(resized, 0, 0, false);
}

void wxImagePanel::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}

bool wxImagePanel::ConvertMatBitmapTowxBitmap(const cv::Mat &matBitmap,
                                              wxBitmap &bitmap) {
    wxCHECK(!matBitmap.empty(), false);
    wxCHECK(matBitmap.type() == CV_8UC3, false);
    wxCHECK(matBitmap.dims == 2, false);
    wxCHECK(bitmap.IsOk(), false);
    wxCHECK(bitmap.GetWidth() == matBitmap.cols &&
                bitmap.GetHeight() == matBitmap.rows,
            false);
    wxCHECK(bitmap.GetDepth() == 24, false);

    wxNativePixelData pixelData(bitmap);
    wxNativePixelData::Iterator pixelDataIt(pixelData);

    if (matBitmap.isContinuous()) {
        const uchar *bgr = matBitmap.data;

        for (int row = 0; row < pixelData.GetHeight(); ++row) {
            pixelDataIt.MoveTo(pixelData, 0, row);

            for (int col = 0; col < pixelData.GetWidth();
                 ++col, ++pixelDataIt) {
                pixelDataIt.Blue() = *bgr++;
                pixelDataIt.Green() = *bgr++;
                pixelDataIt.Red() = *bgr++;
            }
        }
    } else // Is it even possible for Mat with image to be not continous?
    {
        auto matBitmapIt = matBitmap.begin<cv::Vec3b>();

        for (int row = 0; row < pixelData.GetHeight(); ++row) {
            pixelDataIt.MoveTo(pixelData, 0, row);

            for (int col = 0; col < pixelData.GetWidth();
                 ++col, ++pixelDataIt, ++matBitmapIt) {
                pixelDataIt.Blue() = (*matBitmapIt)[0];
                pixelDataIt.Green() = (*matBitmapIt)[1];
                pixelDataIt.Red() = (*matBitmapIt)[2];
            }
        }
    }

    return bitmap.IsOk();
}

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()