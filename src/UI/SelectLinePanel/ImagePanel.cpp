#include <UI/SelectLinePanel/ImagePanel.hpp>

SelectLinePanelImage::SelectLinePanelImage(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id), lineDetection() {
    // SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->imgData = imgData;
    cv::Mat firstImg = this->imgData[count].image.clone();

    img_bitmap = new BBLane(this, Enum::SL_BB_ID);
    img_bitmap->SetImage2(firstImg);

    // img_bitmap->Bind(wxEVT_LEFT_DOWN, &SelectLinePanelImage::OnLeftDown,
    // this);

    lineDetection.SetImage(firstImg);
}

void SelectLinePanelImage::OnCanny() {
    isCanny = !isCanny;
    if (isCanny) {
        wxLogMessage("Show Canny");
        lineDetection.SetImage(imgData[count].image);
        cv::Mat img = lineDetection.GetCanny().clone();
        img_bitmap->SetImage2(img);
        return;
    }
    wxLogMessage("Hide Canny");
    img_bitmap->SetImage2(imgData[count].image);
}

void SelectLinePanelImage::OnHough() {
    img_bitmap->ToggleHough();

    if (img_bitmap->GetIsHough()) {
        wxLogMessage("Show Hough");
        std::vector<cv::Vec4i> l = lineDetection.GetLinesP();
        std::cout << "l: " << l.size() << std::endl;
        img_bitmap->SetLinesP(lineDetection.GetLinesP());
        return;
    }
    wxLogMessage("Hide Hough");
}

void SelectLinePanelImage::OnClear() { img_bitmap->clearLines(); }

void SelectLinePanelImage::checkForLine(wxPoint realMousePos) {
    cv::Point2f mousePos(realMousePos.x, realMousePos.y);
    std::vector<cv::Vec4i> detLines;
    std::vector<cv::Vec4i> linesP = lineDetection.GetLinesP();

    if (linesP.empty()) {
        wxLogMessage("No Lines Found");
        return;
    }

    for (auto line : linesP) {
        if (lineDetection.isPointOnLine(line, mousePos, 3)) {
            detLines.push_back(line);
            wxLogMessage("Line Point1: (%d, %d) Point2: (%d, %d)", line[0],
                         line[1], line[2], line[3]);
        }
    }

    if (detLines.size() == 0) {
        wxLogMessage("No Lines Found");
        return;
    }

    // ! [Possible Error] -> Some Lines might have Different Angle
    cv::Vec4i avgLine = lineDetection.averageLines(detLines);
    wxLogMessage(
        "Found %zd lines from linesP --> Average Line Point1: (%d, %d) "
        "Point2: (%d, %d)",
        detLines.size(), avgLine[0], avgLine[1], avgLine[2], avgLine[3]);
    img_bitmap->addLine(lineDetection.extrapolateLine(
        avgLine, imgData[count].image.size().height));
}

void SelectLinePanelImage::OnSize(wxSizeEvent &e) {
    wxLogMessage("setsize");
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
    // img_bitmap->SetImage2(imgData[count].image);
    // img_bitmap->Refresh();
}

void SelectLinePanelImage::OnLeftDown(wxMouseEvent &e) {
    wxPoint mousePos = e.GetPosition();
    wxPoint realPos = img_bitmap->GetRealMousePos(mousePos);
    wxLogMessage("[LOGGING] Left Mouse Clicked: Current MousePos: (%d, %d) "
                 "---> Real MousePos: (%d, %d)",
                 mousePos.x, mousePos.y, realPos.x, realPos.y);
    checkForLine(realPos);
}

std::vector<cv::Vec4i> SelectLinePanelImage::GetDetectedLines() {
    return img_bitmap->GetDetectedLines();
}

void SelectLinePanelImage::OnPaint(wxPaintEvent &e) {
    std::cout << "from image panel" << std::endl;
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanelImage, wxPanel)
// EVT_SIZE(SelectLinePanelImage::OnSize)
// EVT_PAINT(BBLane::OnPaint)
END_EVENT_TABLE()
