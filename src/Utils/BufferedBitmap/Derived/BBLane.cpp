#include <Utils/BufferedBitmap/Derived/BBLane.hpp>

BBLane::BBLane(wxWindow *parent, wxWindowID id) : BufferedBitmap(parent, id) {
    // SetBackgroundStyle(wxFULL_REPAINT_ON_RESIZE);
    // Bind(wxEVT_PAINT, OnPaint, this);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Connect(wxEVT_PAINT, wxPaintEventHandler(BBLane::OnPaint2));
}

void BBLane::OnPaint2(wxPaintEvent &e) { std::cout << "onPaint2" << std::endl; }
void BBLane::OnPaint(wxPaintEvent &e) {
    wxLogMessage("Painting from derive");
    processRatio();
    // BufferedBitmap::processRatio();

    // clear the buffered image to prevent stacking when resizing
    std::cout << "imhere" << std::endl;
    wxAutoBufferedPaintDC dc(this);
    std::cout << "clear" << std::endl;
    dc.Clear();
    if (img.cols <= 10 || img.rows <= 10) {
        wxLogMessage("invalid image");
        return;
    }
    std::cout << "clone" << std::endl;

    cv::Mat img_cp = img.clone();
    if (isHough) {
        if (linesP.empty()) {
            wxLogMessage("[ERROR] linesP is empty");
        } else {
            for (auto &line : linesP) {
                cv::line(img_cp, cv::Point(line[0], line[1]),
                         cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 3,
                         cv::LINE_AA);
            }
        }
    }

    if (!detLines.empty()) {
        for (auto &line : detLines) {
            cv::line(img_cp, cv::Point(line[0], line[1]),
                     cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0), 3,
                     cv::LINE_AA);
        }
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage2(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
    e.Skip();
}

void BBLane::OnPainttt() {
    wxLogMessage("Painting from 2");
    BufferedBitmap::processRatio();
    cv::Mat img_cp = img.clone();
    if (isHough) {
        if (linesP.empty()) {
            wxLogMessage("[ERROR] linesP is empty");
        } else {
            for (auto &line : linesP) {
                cv::line(img_cp, cv::Point(line[0], line[1]),
                         cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 3,
                         cv::LINE_AA);
            }
        }
    }

    if (!detLines.empty()) {
        for (auto &line : detLines) {
            cv::line(img_cp, cv::Point(line[0], line[1]),
                     cv::Point(line[2], line[3]), cv::Scalar(0, 255, 0), 3,
                     cv::LINE_AA);
        }
    }

    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxAutoBufferedPaintDC dc(this);

    // clear the buffered image to prevent stacking when resizing
    dc.Clear();

    wxImage wximg = matToWxImage(img_rs);
    dc.DrawBitmap(wxBitmap(wximg), 0, 0);
}

void BBLane::SetImage2(cv::Mat &image) {
    img = image.clone();
    wxLogMessage("Setting Image from derived");
    BufferedBitmap::processRatio();
    wxLogMessage("settingBitmap");
    // cv::Mat img_rs;
    // cv::resize(img, img, cv::Size(resizeWidth, resizeHeight));
    wxImage wximg = matToWxImage2(img);
    wxStaticBitmap::SetBitmap(wxBitmap(wximg));
    Refresh();
    // Update();
    // OnPainttt();
}

wxImage BBLane::matToWxImage2(cv::Mat &mat) {
    wxLogMessage("mattoxwimage");
    if (mat.empty()) {
        wxLogMessage("enpty");
        return wxImage();
    } else {
        wxLogMessage("not empty");
    }
    if (mat.type() == CV_8UC3) {
        wxLogMessage("converted");
        cv::cvtColor(mat, RGBImg, cv::COLOR_BGR2RGB);
        // cv::imshow("temp", mat);
        wxImage image(RGBImg.cols, RGBImg.rows, RGBImg.data, true);
        return image;

    } else if (mat.type() == CV_8UC1) {
        wxLogMessage("gray");
        wxImage image(mat.cols, mat.rows, mat.data);
        return image.ConvertToGreyscale();
    } else {
        throw std::runtime_error("Unsupported image format");
        wxLogMessage("unsupp");
    }
}

void BBLane::SetLinesP(const std::vector<cv::Vec4i> &linesP) {
    this->linesP = linesP;
}

void BBLane::ToggleHough() {
    isHough = !isHough;
    Refresh();
}

void BBLane::addLine(cv::Vec4i line) {
    if (detLines.size() <= 1) {
        detLines.push_back(line);
    } else {
        detLines[1] = line;
    }
    Refresh();
}

void BBLane::clearLines() {
    detLines.clear();
    Refresh();
}

std::vector<cv::Vec4i> BBLane::GetDetectedLines() { return detLines; }

bool BBLane::GetIsHough() { return isHough; }

wxPoint BBLane::GetRealMousePos(wxPoint mousePos) {
    wxPoint realMousePos;
    realMousePos.x = mousePos.x * widthRatio;
    realMousePos.y = mousePos.y * heightRatio;
    return realMousePos;
}

// clang-format off
wxBEGIN_EVENT_TABLE(BBLane, BufferedBitmap)
EVT_PAINT(BBLane::OnPaint2)
wxEND_EVENT_TABLE()

