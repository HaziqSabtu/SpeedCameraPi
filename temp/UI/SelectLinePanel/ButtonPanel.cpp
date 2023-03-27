#include <UI/SelectLinePanel/ButtonPanel.hpp>

SelectLinePanelButton::SelectLinePanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Canny_Button = new wxButton(this, Enum::SL_Canny_Button_ID, "Show Canny");
    Hough_Button = new wxButton(this, Enum::SL_Hough_Button_ID, "Show Hough");
    Clear_Button = new wxButton(this, Enum::SL_Clear_Button_ID, "Clear Line");
    Next_Button = new wxButton(this, Enum::SL_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::SL_Prev_Button_ID, "Prev");

    Spacer = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                              wxDefaultSize, wxALIGN_RIGHT);

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Canny_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Hough_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Clear_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Spacer, 1, wxALL | wxCENTER, 5);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);
}

void SelectLinePanelButton::OnCanny() {
    isCanny = !isCanny;
    if (isCanny) {
        Canny_Button->SetLabel("Hide Canny");
    } else {
        Canny_Button->SetLabel("Show Canny");
    }
}

void SelectLinePanelButton::OnHough() {
    isHough = !isHough;
    if (isHough) {
        Hough_Button->SetLabel("Hide Hough");
    } else {
        Hough_Button->SetLabel("Show Hough");
    }
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanelButton, wxPanel)
END_EVENT_TABLE()


/**
* Why casting ImagePanel at constructor not recommended ?
The problem with the approach is that it's not guaranteed that the 
parent passed to the button panel is an instance of the ImagePanel class. 
If it's not, dynamic_cast will return a null pointer and the code will crash.
It's better to pass a pointer to the image panel to the button panel's 
constructor as an argument, as I described in my previous answer, this way you 
can be sure that the pointer passed is the correct one.

tldr: if casting at constructor there is no way to know if the class casted is of panel image class.
it could be any other class which have different structure/methods. therefore code crashed may occur.
*/

