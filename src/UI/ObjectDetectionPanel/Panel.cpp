#include <UI/ObjectDetectionPanel/Panel.hpp>

ObjectDetectionPanel::ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id), objectDetection(rng), imgData(imgData) {

    speedCalculation.SetImageWidth(imgData[c].image.cols);
    wxLogMessage("imgData[c].image.cols: %d", imgData[c].image.cols);

    button_panel =
        new ObjectDetectionPanelButton(this, Enum::SR_BUTTON_PANEL_ID);

    img_bitmap = new ObjectDetectionBitmap(this, Enum::OD_BB_ID);
    img_bitmap->SetImage(imgData[c].image);
    img_bitmap->Bind(wxEVT_SIZE, &ObjectDetectionPanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    timer.SetOwner(this, wxID_ANY);
    Connect(wxID_ANY, wxEVT_TIMER,
            wxTimerEventHandler(ObjectDetectionPanel::OnTimer));

    isBBox = false;
    isOptF = false;
    isBotL = false;
    isLine = false;
}

void ObjectDetectionPanel::OnTimer(wxTimerEvent &e) {
    if (!isRunning) {
        wxLogMessage("Timer stopped");
        button_panel->enableAllButtons();
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
        timer.Stop();
        return;
    }
    wxLogMessage("Timer running");
}

void ObjectDetectionPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::OD_Next_Button_ID) {
        wxLogMessage("Next button pressed");
        OnIncrement();

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
    }

    if (e.GetId() == Enum::OD_BBox_Button_ID) {
        wxLogMessage("BBox button pressed");
        isBBox = !isBBox;
        wxLogMessage("toggleBBOX");
        button_panel->OnBBox();
        wxLogMessage("OnBBOX");
        if (isBBox) {
            wxLogMessage("handleBBOX");
            handleBBox();
            wxLogMessage("drawBitMap");
            img_bitmap->drawBitMap();
            wxLogMessage("return");
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

    if (e.GetId() == Enum::OD_Speed_Button_ID) {
        wxLogMessage("Speed button pressed");
        button_panel->OnSpeed();
        handleSpeed();
    }
}

void ObjectDetectionPanel::handleBBox() {
    bbox = &objectDetection.GetRect(opticalFlowPoints[c]);
    img_bitmap->SetBBox(bbox);
}

void ObjectDetectionPanel::handleOptF() {
    if (opticalFlowPoints.empty() == 0) {
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
    }
    result = &objectDetection.GetOFPoints(opticalFlowPoints, c);
    img_bitmap->SetResult(result);
}

void ObjectDetectionPanel::handleBotL() {
    if (opticalFlowPoints.empty()) {
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
    }
    bottomLine = &objectDetection.GetBottomLine(opticalFlowPoints[c],
                                                imgData[c].image.cols);
    img_bitmap->SetBottomLine(bottomLine);
}

void ObjectDetectionPanel::handleSpeed() {
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

    // imgData = sl_panel->GetImgData();

    // if (imgData.empty()) {
    //     return;
    // }

    if (opticalFlowPoints.empty()) {
        objectDetectionThread =
            new ObjectDetectionThread(&objectDetection, &imgData, &isRunning);
        objectDetectionThread->Create();
        objectDetectionThread->Run();
        timer.Start(33);
    }

    selectedLines = sl_panel->GetSelectedLines();
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, ObjectDetectionPanel::OnButton)
END_EVENT_TABLE()
