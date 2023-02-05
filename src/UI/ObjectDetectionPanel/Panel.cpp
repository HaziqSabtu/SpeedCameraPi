#include <UI/ObjectDetectionPanel/Panel.hpp>

ObjectDetectionPanel::ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    cv::RNG rng;
    ObjectDetection objD(rng);
    SpeedCalculation spdC(imgData[0].image.cols);
    wxLogMessage("Image Width: %d", imgData[0].image.cols);

    button_panel =
        new ObjectDetectionPanelButton(this, Enum::SR_BUTTON_PANEL_ID);

    img_panel = new ObjectDetectionPanelImage(this, Enum::SR_IMG_PANEL_ID, objD,
                                              spdC, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void ObjectDetectionPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::OD_Next_Button_ID) {
        wxLogMessage("Next button pressed");
        img_panel->OnButtonIncrement();
    }

    if (e.GetId() == Enum::OD_BBox_Button_ID) {
        wxLogMessage("BBox button pressed");
        button_panel->OnBBox();
        img_panel->OnBBox();
    }

    if (e.GetId() == Enum::OD_OptF_Button_ID) {
        wxLogMessage("OptF button pressed");
        button_panel->OnOptF();
        img_panel->OnOptF();
    }

    if (e.GetId() == Enum::OD_BotL_Button_ID) {
        wxLogMessage("BotL button pressed");
        button_panel->OnBotL();
        img_panel->OnBotL();
    }

    if (e.GetId() == Enum::OD_Line_Button_ID) {
        wxLogMessage("Line button pressed");
        button_panel->OnLine();
        img_panel->OnLine();
    }

    if (e.GetId() == Enum::OD_Speed_Button_ID) {
        wxLogMessage("Speed button pressed");
        button_panel->OnSpeed();
        img_panel->OnSpeed();
    }
}

void ObjectDetectionPanel::OnPageChange() {
    if (img_panel->GetOpticalFlowPoints().size() == 0) {
        img_panel->runDetection();
    }

    SelectLinePanelImage *img_panel_lineD =
        dynamic_cast<SelectLinePanelImage *>(
            GetParent()->FindWindow(Enum::SL_IMG_PANEL_ID));
    img_panel->SetLine(img_panel_lineD->GetDetectedLines());
    button_panel->enableAllButtons();
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, ObjectDetectionPanel::OnButton)
END_EVENT_TABLE()
