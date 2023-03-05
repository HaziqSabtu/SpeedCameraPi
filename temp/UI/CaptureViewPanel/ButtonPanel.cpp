#include <UI/CaptureViewPanel/ButtonPanel.hpp>

CaptureViewPanelButton::CaptureViewPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    Next_Button = new wxButton(this, Enum::CV_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::CV_Prev_Button_ID, "Prev");

    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(CaptureViewPanelButton, wxPanel)
END_EVENT_TABLE()

