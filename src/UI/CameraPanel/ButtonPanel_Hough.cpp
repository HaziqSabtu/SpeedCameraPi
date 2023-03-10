#include <UI/CameraPanel/ButtonPanel_Hough.hpp>

ButtonPanelHough::ButtonPanelHough(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    Canny_Button = new ButtonCanny(this, Enum::CP_Canny_Button_ID);
    Hough_Button = new ButtonHough(this, Enum::CP_Hough_Button_ID);
    ClearLine_Button =
        new wxButton(this, Enum::CP_Clear_Button_ID, "Clear Line");
    Reset_Button = new wxButton(this, wxID_ANY, "Reset");
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
}

void ButtonPanelHough::DisableAllButtons() {}

void ButtonPanelHough::EnableAllButtons() {}

void ButtonPanelHough::OnButton(wxCommandEvent &e) {
    int id = e.GetId();
    std::cout << "ButtonPanelHough::OnButton: " << id << std::endl;
    e.Skip();
}
// clang-format off
BEGIN_EVENT_TABLE(ButtonPanelHough, wxPanel)
 EVT_BUTTON(wxID_ANY, ButtonPanelHough::OnButton)
END_EVENT_TABLE()

