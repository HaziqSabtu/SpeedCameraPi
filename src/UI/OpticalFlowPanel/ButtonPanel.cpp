#include <UI/OpticalFlowPanel/ButtonPanel.hpp>

OpticalFlowPanelButton::OpticalFlowPanelButton(wxWindow *parent, wxWindowID id,
                                               wxWindowID img_id)
    : wxPanel(parent, id) {
    IMG_PANEL_ID = img_id;
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::OF_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::OF_Prev_Button_ID, "Prev");
    Sel_Button = new wxButton(this, Enum::OF_Sel_Button_ID, "Select");
    RemoveROI_Button =
        new wxButton(this, Enum::OF_RemoveROI_Button_ID, "Remove ROI");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Sel_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(RemoveROI_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);
}

void OpticalFlowPanelButton::OnButton(wxCommandEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(IMG_PANEL_ID));
    if (e.GetId() == Enum::OF_Next_Button_ID) {
        img_panel->OnButtonIncrement();
    } else if (e.GetId() == Enum::OF_Prev_Button_ID) {
        img_panel->OnButtonDecrement();
    } else if (e.GetId() == Enum::OF_Sel_Button_ID) {
        // todo set selected IMG
    }
}

void OpticalFlowPanelButton::OnKeyPress(wxKeyEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(IMG_PANEL_ID));
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        img_panel->OnButtonIncrement();
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        img_panel->OnButtonDecrement();
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        // todo set selected IMG
    }
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanelButton, wxPanel)
EVT_BUTTON(wxID_ANY, OpticalFlowPanelButton::OnButton)
EVT_KEY_DOWN(OpticalFlowPanelButton::OnKeyPress)
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

