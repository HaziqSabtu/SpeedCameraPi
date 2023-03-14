#include <UI/CameraPanel/ButtonPanel_Hough.hpp>

ButtonPanelHough::ButtonPanelHough(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), isInit(false) {

    Canny_Button = new ButtonCanny(this, Enum::CP_Canny_Button_ID);
    Hough_Button = new ButtonHough(this, Enum::CP_Hough_Button_ID);
    ClearLine_Button =
        new wxButton(this, Enum::CP_Clear_Button_ID, "Clear Line");
    Reset_Button = new wxButton(this, Enum::CP_Reset_Button_ID, "Reset");
    Next_Button = new wxButton(this, Enum::CP_Next_Button_ID, ">>");
    Prev_Button = new wxButton(this, Enum::CP_Prev_Button_ID, "<<");
    Spacer = new wxStaticText(this, wxID_ANY, "");

    nextprev_sizer = new wxBoxSizer(wxHORIZONTAL);
    nextprev_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 0);
    nextprev_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 0);

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(nextprev_sizer, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Canny_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Hough_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(ClearLine_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Reset_Button, 0, wxALL | wxCENTER, 5);

    this->SetSizer(button_sizer);

    Bind(wxEVT_SHOW, &ButtonPanelHough::OnShow, this);
    Bind(c_HOUGH_EVENT, &ButtonPanelHough::OnHough, this);
}

void ButtonPanelHough::SetDefaultState() { this->isProcess = false; }

void ButtonPanelHough::DisableAllButtons() {
    Canny_Button->Disable();
    Hough_Button->Disable();
    ClearLine_Button->Disable();
    Next_Button->Disable();
    Prev_Button->Disable();
}

void ButtonPanelHough::EnableAllButtons() {
    Canny_Button->Enable();
    Hough_Button->Enable();
    ClearLine_Button->Enable();
    Next_Button->Enable();
    Prev_Button->Enable();
}

void ButtonPanelHough::OnButton(wxCommandEvent &e) {
    int id = e.GetId();
    std::cout << "ButtonPanelHough::OnButton: " << id << std::endl;
    e.Skip();
}

void ButtonPanelHough::OnShow(wxShowEvent &e) {
    if (!isInit) {
        isInit = true;
        return;
    }
    if (e.IsShown() && !isProcess) {
        isProcess = true;
        wxCommandEvent processImageEvent(c_PROCESS_IMAGE_EVENT, PROCESS_BEGIN);
        wxPostEvent(this, processImageEvent);
    }
    e.Skip();
}

void ButtonPanelHough::OnHough(wxCommandEvent &e) {
    if (e.GetId() == HOUGH_START) {
        std::cout << "ButtonPanelHough::OnHough: HOUGH_START" << std::endl;
        DisableAllButtons();
    } else if (e.GetId() == HOUGH_END) {
        std::cout << "ButtonPanelHough::OnHough: HOUGH_END" << std::endl;
        EnableAllButtons();
    }
    e.Skip();
}

bool ButtonPanelHough::GetCannyState() { return Canny_Button->GetState(); }

bool ButtonPanelHough::GetHoughState() { return Hough_Button->GetState(); }

// clang-format off
BEGIN_EVENT_TABLE(ButtonPanelHough, wxPanel)
 EVT_BUTTON(wxID_ANY, ButtonPanelHough::OnButton)
END_EVENT_TABLE()

