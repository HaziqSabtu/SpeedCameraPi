#include <UI/SelectLinePanel/Panel.hpp>

SelectLinePanel::SelectLinePanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), lineDetection() {

    ptns = new std::vector<cv::Point2f>();
    // houghLines = new std::vector<Detection>();
    selectedLines = new std::vector<Line>();

    button_panel = new SelectLinePanelButton(this, Enum::SL_BUTTON_PANEL_ID);

    img_bitmap = new SelectLineBitmap(this, Enum::SL_BITMAP_ID);
    img_bitmap->SetPoints(ptns);
    // img_bitmap->SetHoughLines(houghLines);
    img_bitmap->setSelectedLines(selectedLines);
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &SelectLinePanel::OnLeftDown, this);
    img_bitmap->Bind(wxEVT_SIZE, &SelectLinePanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

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
        button_panel->OnCanny();
        isCanny = !isCanny;
        if (isCanny) {
            lineDetection.SetImage(imgData[c].image);
            img_bitmap->SetImage(lineDetection.GetCanny());
            return;
        }
        img_bitmap->SetImage(imgData[c].image);
    }

    if (e.GetId() == Enum::SL_Hough_Button_ID) {
        button_panel->OnHough();
        isHough = !isHough;
        if (isHough) {
            lineDetection.SetImage(imgData[c].image);
            // houghLines = &lineDetection.GetLinesP();
            // img_bitmap->SetHoughLines(houghLines);
            img_bitmap->SetHoughLines(lineDetection.GetLines());
            img_bitmap->drawBitMap();
            return;
        }
        houghLines->clear();
        // img_bitmap->SetHoughLines(nullptr);
        img_bitmap->SetHoughLines(std::vector<Line>());
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::SL_Clear_Button_ID) {
        ptns->clear();
        selectedLines->clear();
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::SL_Next_Button_ID) {
        OnIncrement();
    }

    if (e.GetId() == Enum::SL_Prev_Button_ID) {
        OnDecrement();
    }
}

void SelectLinePanel::OnIncrement() {
    c = (c >= imgData.size() - 1) ? c : c + 1;
    img_bitmap->SetImage(imgData[c].image);
    lineDetection.SetImage(imgData[c].image);
    // houghLines = &lineDetection.GetLinesP();
    // img_bitmap->SetHoughLines(houghLines);
}

void SelectLinePanel::OnDecrement() {
    c = (c <= 0) ? c : c - 1;
    img_bitmap->SetImage(imgData[c].image);
    lineDetection.SetImage(imgData[c].image);
    // houghLines = &lineDetection.GetLinesP();
    // img_bitmap->SetHoughLines(houghLines);
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
    std::vector<Line> detLines;
    std::vector<Line> linesP = lineDetection.GetLines();

    if (linesP.empty()) {
        wxLogMessage("No Lines Available");
        return;
    }

    for (auto line : linesP) {
        if (line.isIntersect(mousePos, 20)) {
            detLines.push_back(line);
        }
    }

    if (detLines.size() == 0) {
        wxLogMessage("No Lines Found");
        return;
    }

    Line avgLine = Line::Average(detLines);
    addLine(avgLine.Extrapolate(imgData[c].image));
}

void SelectLinePanel::addPoints(wxPoint realMousePos) {
    if (ptns == NULL) {
        ptns = new std::vector<cv::Point2f>();
        img_bitmap->SetPoints(ptns);
    }
    ptns->push_back(cv::Point2f(realMousePos.x, realMousePos.y));
}

void SelectLinePanel::addLine(Line line) {
    if (selectedLines == NULL) {
        selectedLines = new std::vector<Line>();
        img_bitmap->setSelectedLines(selectedLines);
    }

    if (selectedLines->size() <= 1) {
        selectedLines->push_back(line);
    } else {
        selectedLines->at(1) = line;
    }
}

std::vector<Line> SelectLinePanel::GetSelectedLines() {
    if (selectedLines == NULL || selectedLines->empty()) {
        return std::vector<Line>();
    }
    return *selectedLines;
}

std::vector<ImageData> SelectLinePanel::GetImgData() { return imgData; }

void SelectLinePanel::OnPageChange() {
    CameraPanel *cp_panel =
        dynamic_cast<CameraPanel *>(GetParent()->FindWindow(Enum::CP_Panel_ID));
    imgData = cp_panel->GetImgData();
    if (imgData.empty()) {
        wxLogMessage("No Images Available");
        return;
    }
    img_bitmap->SetImage(imgData[c].image);
    img_bitmap->drawBitMap();
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanel, wxPanel)
    EVT_BUTTON(wxID_ANY, SelectLinePanel::OnButton)
END_EVENT_TABLE()