#include <UI/CameraPanel/Panel_Button_Result.hpp>

PanelButtonResult::PanelButtonResult(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), isInit(false) {
    BBox_Button = new ButtonBBox(this, Enum::CP_BBox_Button_ID);
    BotL_Button = new ButtonBotL(this, Enum::CP_BotL_Button_ID);
    OFPnt_Button = new ButtonOFPnt(this, Enum::CP_OptF_Button_ID);
    SelL_Button = new ButtonSelL(this, Enum::CP_SelL_Button_ID);
    Replay_Button = new wxButton(this, Enum::CP_Replay_Button_ID, "Replay");
    Reselect_Button =
        new wxButton(this, Enum::CP_Reselect_Button_ID, "Reselect");

    Reset_Button = new wxButton(this, wxID_ANY, "Reset");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Replay_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(BBox_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(BotL_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(OFPnt_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(SelL_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Reselect_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Reset_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);

    Bind(wxEVT_SHOW, &PanelButtonResult::OnShow, this);
}

void PanelButtonResult::DisableAllButtons() {
    BBox_Button->Disable();
    BotL_Button->Disable();
    OFPnt_Button->Disable();
    SelL_Button->Disable();
    Reset_Button->Disable();
    Replay_Button->Disable();
    Reselect_Button->Disable();
}

void PanelButtonResult::EnableAllButtons() {
    BBox_Button->Enable();
    BotL_Button->Enable();
    OFPnt_Button->Enable();
    SelL_Button->Enable();
    Reset_Button->Enable();
    Replay_Button->Enable();
    Reselect_Button->Enable();
}

void PanelButtonResult::OnButton(wxCommandEvent &e) { e.Skip(); }

void PanelButtonResult::OnShow(wxShowEvent &e) {
    if (!isInit) {
        isInit = true;
        return;
    }
    e.Skip();
}

// clang-format off
BEGIN_EVENT_TABLE(PanelButtonResult, wxPanel)
 EVT_BUTTON(wxID_ANY, PanelButtonResult::OnButton)
END_EVENT_TABLE()

