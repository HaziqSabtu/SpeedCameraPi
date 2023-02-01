#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>

ObjectDetectionPanelButton::ObjectDetectionPanelButton(wxWindow *parent,
                                                       wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::OD_Next_Button_ID, "Next");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanelButton, wxPanel)
END_EVENT_TABLE()


/*
Why casting ImagePanel at constructor not recommended ?
The problem with the approach is that it's not guaranteed that the 
parent passed to the button panel is an instance of the ImagePanel class. 
If it's not, dynamic_cast will return a null pointer and the code will crash.
It's better to pass a pointer to the image panel to the button panel's 
constructor as an argument, as I described in my previous answer, this way you 
can be sure that the pointer passed is the correct one.

tldr: if casting at constructor there is no way to know if the class casted is of panel image class.
it could be any other class which have different structure/methods. therefore code crashed may occur.
*/

