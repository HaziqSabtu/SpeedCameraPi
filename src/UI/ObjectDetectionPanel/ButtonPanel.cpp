#include <UI/ObjectDetectionPanel/ButtonPanel.hpp>

ObjectDetectionPanelButton::ObjectDetectionPanelButton(wxWindow *parent,
                                                       wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::OD_Next_Button_ID, "Next");
    BBox_Button = new wxButton(this, Enum::OD_BBox_Button_ID, "BBox");
    OptF_Button = new wxButton(this, Enum::OD_OptF_Button_ID, "OptF");
    BotL_Button = new wxButton(this, Enum::OD_BotL_Button_ID, "BotL");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(BBox_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(OptF_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(BotL_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);

    // Disable buttons
    Next_Button->Disable();
    BBox_Button->Disable();
    OptF_Button->Disable();
    BotL_Button->Disable();
}

void ObjectDetectionPanelButton::enableAllButtons() {
    wxLogMessage("Enabling all buttons");
    Next_Button->Enable();
    BBox_Button->Enable();
    OptF_Button->Enable();
    BotL_Button->Enable();
}

void ObjectDetectionPanelButton::OnBBox() {
    isBBox = !isBBox;
    if (isBBox) {
        BBox_Button->SetLabel("Hide BBox");
    } else {
        BBox_Button->SetLabel("Show BBox");
    }
}

void ObjectDetectionPanelButton::OnOptF() {
    isOptF = !isOptF;
    if (isOptF) {
        OptF_Button->SetLabel("Hide OptF");
    } else {
        OptF_Button->SetLabel("Show OptF");
    }
}

void ObjectDetectionPanelButton::OnBotL() {
    isBotL = !isBotL;
    if (isBotL) {
        BotL_Button->SetLabel("Hide BotL");
    } else {
        BotL_Button->SetLabel("Show BotL");
    }
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

