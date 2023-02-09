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

    isBBox = false;
    isOptF = false;
    isBotL = false;
    isLine = false;
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
    wxLogMessage("Object Detection Page Change");
    if (opticalFlowPoints.empty()) {
        objectDetection.runDetection(imgData);
        opticalFlowPoints = objectDetection.GetOpticalFlowPoints(true);
    }
    wxLogMessage("Object Detection Page Change 2");

    SelectLinePanel *sl_panel = dynamic_cast<SelectLinePanel *>(
        GetParent()->FindWindow(Enum::SL_Panel_ID));
    selectedLines = sl_panel->GetSelectedLines();

    button_panel->enableAllButtons();
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, ObjectDetectionPanel::OnButton)
END_EVENT_TABLE()
