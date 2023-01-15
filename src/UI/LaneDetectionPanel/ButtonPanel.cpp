#include <UI/LaneDetectionPanel/ButtonPanel.hpp>

LaneDetectionPanelButton::LaneDetectionPanelButton(wxWindow *parent,
                                                   wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::LD_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::LD_Prev_Button_ID, "Prev");
    Run_Button = new wxButton(this, Enum::LD_Run_Button_ID, "Run Algorithm");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Run_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);

    Next_Button->Disable();
    Prev_Button->Disable();
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
}

// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanelButton, wxPanel)
    // EVT_BUTTON(Enum::LD_Next_Button_ID, LaneDetectionPanelButton::OnNext)
    // EVT_BUTTON(Enum::LD_Prev_Button_ID, LaneDetectionPanelButton::OnPrev)
    EVT_BUTTON(Enum::LD_Run_Button_ID, LaneDetectionPanelButton::OnRunAlgorithm)
END_EVENT_TABLE()

