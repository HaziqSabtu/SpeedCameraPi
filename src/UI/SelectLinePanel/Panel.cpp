#include <UI/SelectLinePanel/Panel.hpp>

SelectLinePanel::SelectLinePanel(wxWindow *parent, wxWindowID id,
                                 std::vector<ImgData> &imgData)
    : wxPanel(parent, id), imgData(imgData), lineDetection() {

    ptns = new std::vector<cv::Point2f>();
    houghLines = new std::vector<cv::Vec4i>();
    selectedLines = new std::vector<cv::Vec4i>();

    button_panel = new SelectLinePanelButton(this, Enum::SL_BUTTON_PANEL_ID);

    img_bitmap = new SelectLineBitmap(this, Enum::SL_BB_ID);
    img_bitmap->SetPoints(ptns);
    img_bitmap->SetHoughLines(houghLines);
    img_bitmap->setSelectedLines(selectedLines);
    img_bitmap->SetImage(imgData[c].image);
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &SelectLinePanel::OnLeftDown, this);
    img_bitmap->Bind(wxEVT_SIZE, &SelectLinePanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    lineDetection.SetImage(imgData[c].image);

    isHough = false;
    isCanny = false;
}

SelectLinePanel::~SelectLinePanel() {
    delete button_panel;
    delete img_bitmap;
    delete main_sizer;
    delete ptns;
    delete houghLines;
    delete selectedLines;
}

void SelectLinePanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::SL_Canny_Button_ID) {
        wxLogMessage("oncanny");
        button_panel->OnCanny();
        if (!isCanny) {
            isCanny = !isCanny;
            lineDetection.SetImage(imgData[c].image);
            img_bitmap->SetImage(lineDetection.GetCanny());
            return;
        }
        isCanny = !isCanny;
        ++c;
        img_bitmap->SetImage(imgData[c].image);
    }

    if (e.GetId() == Enum::SL_Hough_Button_ID) {
        button_panel->OnHough();
        if (!isHough) {
            isHough = !isHough;
            lineDetection.SetImage(imgData[c].image);
            houghLines = &lineDetection.GetLinesP();
            img_bitmap->SetHoughLines(houghLines);
            img_bitmap->drawBitMap();
            return;
        }
        isHough = !isHough;
        houghLines->clear();
        img_bitmap->SetHoughLines(NULL);
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::SL_Clear_Button_ID) {
        ptns->clear();
        selectedLines->clear();
        img_bitmap->drawBitMap();
    }
}

void SelectLinePanel::OnLeftDown(wxMouseEvent &e) {
    wxPoint mousePos = e.GetPosition();
    wxPoint realPos = img_bitmap->GetRealMousePos(mousePos);
    addPoints(realPos);
    checkForLine(realPos);
    img_bitmap->drawBitMap();
}

void SelectLinePanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void SelectLinePanel::checkForLine(wxPoint realMousePos) {
    cv::Point2f mousePos(realMousePos.x, realMousePos.y);
    std::vector<cv::Vec4i> detLines;
    std::vector<cv::Vec4i> &linesP = lineDetection.GetLinesP();

    if (linesP.empty()) {
        wxLogMessage("No Lines Available");
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
    addLine(
        lineDetection.extrapolateLine(avgLine, imgData[c].image.size().height));
}

void SelectLinePanel::addPoints(wxPoint realMousePos) {
    if (ptns == NULL) {
        ptns = new std::vector<cv::Point2f>();
        img_bitmap->SetPoints(ptns);
    }
    ptns->push_back(cv::Point2f(realMousePos.x, realMousePos.y));
}

void SelectLinePanel::addLine(cv::Vec4i line) {
    if (selectedLines == NULL) {
        selectedLines = new std::vector<cv::Vec4i>();
        img_bitmap->setSelectedLines(selectedLines);
    }

    if (selectedLines->size() <= 1) {
        selectedLines->push_back(line);
    } else {
        selectedLines->at(1) = line;
    }
}

std::vector<cv::Vec4i> SelectLinePanel::GetSelectedLines() {
    wxLogMessage("selecting lines");
    if (selectedLines == NULL || selectedLines->empty()) {
        wxLogMessage("No Lines Selected");
        return std::vector<cv::Vec4i>();
    } else {
        wxLogMessage("Lines Selected not empty");
        wxLogMessage("Size: %zd", selectedLines->size());
    }
    return *selectedLines;
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanel, wxPanel)
    EVT_BUTTON(wxID_ANY, SelectLinePanel::OnButton)
END_EVENT_TABLE()
