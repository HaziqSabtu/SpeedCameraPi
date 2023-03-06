#include <UI/ObjectDetectionPanel/Panel.hpp>

ObjectDetectionPanel::ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                                           AppConfig *config)
    : wxPanel(parent, id), objectDetection(rng) {
    button_panel =
        new ObjectDetectionPanelButton(this, Enum::SR_BUTTON_PANEL_ID);

    img_bitmap = new ObjectDetectionBitmap(this, Enum::OD_BITMAP_ID);
    img_bitmap->Bind(wxEVT_SIZE, &ObjectDetectionPanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    CameraPanelRefreshRate = config->GetResultPanelRefreshRate();
    SetSizer(main_sizer);
    Fit();

    timer.Bind(wxEVT_TIMER, &ObjectDetectionPanel::OnTimer, this);

    loopTimer.Bind(wxEVT_TIMER, &ObjectDetectionPanel::OnImageLoop, this);

    isBBox = false;
    isOptF = false;
    isBotL = false;
    isLine = false;
}

// todo: better implementation
void ObjectDetectionPanel::OnTimer(wxTimerEvent &e) {
    if (!isRunning) {
        wxLogMessage("Timer stopped");
        button_panel->enableAllButtons();
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
        handleSpeed();
        calculatedSpeed = speedCalculation.GetAvgSpeed();
        img_bitmap->SetSpeed(&calculatedSpeed);
        timer.Stop();
        loopTimer.Start(CameraPanelRefreshRate);
        return;
    }
}

void ObjectDetectionPanel::OnImageLoop(wxTimerEvent &e) {
    if (c < imgData.size()) {
        img_bitmap->SetImage(imgData[c].image);
        if (isBBox) {
            handleBBox();
        }

        if (isOptF) {
            handleOptF();
        }

        if (isBotL) {
            handleBotL();
        }
        img_bitmap->drawBitMap();
        c++;
    } else {
        loopTimer.Stop();
    }
}

void ObjectDetectionPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::OD_Replay_Button_ID) {
        c = 0;
        loopTimer.Start(CameraPanelRefreshRate);
    }

    if (e.GetId() == Enum::OD_BBox_Button_ID) {
        wxLogMessage("BBox button pressed");
        isBBox = !isBBox;
        button_panel->OnBBox();
        if (isBBox) {
            handleBBox();
            img_bitmap->drawBitMap();
            return;
        }
        img_bitmap->SetBBox(nullptr);
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::OD_OptF_Button_ID) {
        wxLogMessage("OptF button pressed");
        isOptF = !isOptF;
        button_panel->OnOptF();
        if (isOptF) {
            handleOptF();
            img_bitmap->drawBitMap();
            return;
        }
        img_bitmap->SetResult(nullptr);
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::OD_BotL_Button_ID) {
        wxLogMessage("BotL button pressed");
        isBotL = !isBotL;
        button_panel->OnBotL();
        if (isBotL) {
            handleBotL();
            img_bitmap->drawBitMap();
            return;
        }
        img_bitmap->SetBottomLine(nullptr);
        img_bitmap->drawBitMap();
    }

    if (e.GetId() == Enum::OD_Line_Button_ID) {
        wxLogMessage("Line button pressed");
        isLine = !isLine;
        button_panel->OnLine();
        if (isLine) {
            img_bitmap->SetSelectedLines(selectedLines);
            img_bitmap->drawBitMap();
            return;
        }
        img_bitmap->SetSelectedLines(std::vector<cv::Vec4i>());
        img_bitmap->drawBitMap();
    }
}

void ObjectDetectionPanel::handleBBox() {
    if (c < opticalFlowPoints.size()) {
        bbox = &objectDetection.GetRect(opticalFlowPoints[c]);
    }
    img_bitmap->SetBBox(bbox);
}

void ObjectDetectionPanel::handleOptF() {
    if (opticalFlowPoints.empty() == 0) {
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
    }
    if (c < opticalFlowPoints.size()) {
        result = &objectDetection.GetOFPoints(opticalFlowPoints, c);
    }
    img_bitmap->SetResult(result);
}

void ObjectDetectionPanel::handleBotL() {
    if (opticalFlowPoints.empty()) {
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
    }

    if (c < opticalFlowPoints.size()) {
        bottomLine = &objectDetection.GetBottomLine(opticalFlowPoints[c],
                                                    imgData[c].image.cols);
    }
    img_bitmap->SetBottomLine(bottomLine);
}

void ObjectDetectionPanel::handleSpeed() {
    speedCalculation.SetImageWidth(imgData[c].image.cols);
    speedCalculation.SetLine(selectedLines);
    speedCalculation.runCalculation(
        speedCalculation.toSpeedData(imgData, opticalFlowPoints));
}

void ObjectDetectionPanel::OnIncrement() {
    c = (c >= imgData.size() - 1) ? c : c + 1;
    img_bitmap->SetImage(imgData[c].image);
}

void ObjectDetectionPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void ObjectDetectionPanel::OnPageChange() {

    SelectLinePanel *sl_panel = dynamic_cast<SelectLinePanel *>(
        GetParent()->FindWindow(Enum::SL_Panel_ID));

    button_panel->disableAllButtons();
    timer.Stop();
    imgData.clear();
    imgData = sl_panel->GetImgData();
    img_bitmap->SetImage(imgData[0].image);
    img_bitmap->drawBitMap();

    if (imgData.empty()) {
        return;
    }

    // if (opticalFlowPoints.empty()) {
    objectDetectionThread =
        new ObjectDetectionThread(&objectDetection, &imgData, &isRunning);
    objectDetectionThread->Create();
    objectDetectionThread->Run();
    timer.Start(33);

    // selectedLines = sl_panel->GetSelectedLines();
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, ObjectDetectionPanel::OnButton)
END_EVENT_TABLE()
