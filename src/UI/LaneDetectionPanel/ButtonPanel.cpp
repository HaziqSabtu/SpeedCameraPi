#include <UI/LaneDetectionPanel/ButtonPanel.hpp>

LaneDetectionPanelButton::LaneDetectionPanelButton(wxWindow *parent,
                                                   wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Run_Button = new wxButton(this, Enum::LD_Run_Button_ID, "Run Algorithm");
    Next_Button = new wxButton(this, Enum::LD_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::LD_Prev_Button_ID, "Prev");
    Left_Button = new wxButton(this, Enum::LD_Left_Button_ID, "Left");
    Right_Button = new wxButton(this, Enum::LD_Right_Button_ID, "Right");
    Both_Button = new wxButton(this, Enum::LD_Both_Button_ID, "Both");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Run_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Left_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Right_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Both_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);

    Next_Button->Disable();
    Prev_Button->Disable();
    Left_Button->Disable();
    Right_Button->Disable();
    Both_Button->Disable();
}

void LaneDetectionPanelButton::OnRunAlgorithm(wxCommandEvent &e) {
    Run_Button->Disable();
    Run_Button->SetLabel("Running...");
    LaneDetectionPanelImage *img_panel =
        dynamic_cast<LaneDetectionPanelImage *>(
            GetParent()->FindWindow(Enum::LD_IMG_PANEL_ID));
    img_panel->RunLaneDetection();
    Run_Button->SetLabel("Finished");

    Next_Button->Enable();
    Prev_Button->Enable();

    Both_Button->Enable();
    Left_Button->Enable();
    Right_Button->Enable();
}

void LaneDetectionPanelButton::OnNext(wxCommandEvent &e) {
    LaneDetectionPanelImage *img_panel =
        dynamic_cast<LaneDetectionPanelImage *>(
            GetParent()->FindWindow(Enum::LD_IMG_PANEL_ID));
    img_panel->OnIncrement();
}

void LaneDetectionPanelButton::OnPrev(wxCommandEvent &e) {
    LaneDetectionPanelImage *img_panel =
        dynamic_cast<LaneDetectionPanelImage *>(
            GetParent()->FindWindow(Enum::LD_IMG_PANEL_ID));
    img_panel->OnDecrement();
}

void LaneDetectionPanelButton::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::LD_Both_Button_ID) {
        Left_Button->Disable();
        Right_Button->Disable();
        // huh ?
    }

    if (e.GetId() == Enum::LD_Left_Button_ID) {
        // Both_Button->Disable();
        // Right_Button->Disable();
        LaneDetectionPanelImage *img_panel =
            dynamic_cast<LaneDetectionPanelImage *>(
                GetParent()->FindWindow(Enum::LD_IMG_PANEL_ID));
        img_panel->SetLeftData();
    }

    if (e.GetId() == Enum::LD_Right_Button_ID) {
        Both_Button->Disable();
        Left_Button->Disable();
    }
}

// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanelButton, wxPanel)
    EVT_BUTTON(Enum::LD_Next_Button_ID, LaneDetectionPanelButton::OnNext)
    EVT_BUTTON(Enum::LD_Prev_Button_ID, LaneDetectionPanelButton::OnPrev)
    EVT_BUTTON(Enum::LD_Run_Button_ID, LaneDetectionPanelButton::OnRunAlgorithm)
    EVT_BUTTON(wxID_ANY, LaneDetectionPanelButton::OnButton)
END_EVENT_TABLE()

