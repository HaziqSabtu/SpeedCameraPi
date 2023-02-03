#include <UI/ObjectDetectionPanel/Panel.hpp>

ObjectDetectionPanel::ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    cv::RNG rng;
    ObjectDetection objD(rng);
    SpeedCalculation spdC;

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
        img_panel->OnBBox();
        button_panel->OnBBox();
    }

    if (e.GetId() == Enum::OD_OptF_Button_ID) {
        wxLogMessage("OptF button pressed");
        img_panel->OnOptF();
        button_panel->OnOptF();
    }

    if (e.GetId() == Enum::OD_BotL_Button_ID) {
        wxLogMessage("BotL button pressed");
        img_panel->OnBotL();
        button_panel->OnBotL();
    }

    if (e.GetId() == Enum::OD_Line_Button_ID) {
        wxLogMessage("Line button pressed");
        img_panel->OnLine();
        button_panel->OnLine();
    }

    if (e.GetId() == Enum::OD_Speed_Button_ID) {
        wxLogMessage("Speed button pressed");
        img_panel->OnSpeed();
        button_panel->OnSpeed();
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
