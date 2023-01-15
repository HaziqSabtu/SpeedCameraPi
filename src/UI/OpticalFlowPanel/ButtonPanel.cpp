#include <UI/OpticalFlowPanel/ButtonPanel.hpp>

OpticalFlowPanelButton::OpticalFlowPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::OF_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::OF_Prev_Button_ID, "Prev");
    Track_Button = new wxButton(this, Enum::OF_Track_Button_ID, "Track Object");
    RemoveROI_Button =
        new wxButton(this, Enum::OF_RemoveROI_Button_ID, "Remove ROI");
    Optical_Button =
        new wxButton(this, Enum::OF_Optical_Button_ID, "Optical Flow");
    Eval_Button = new wxButton(this, Enum::OF_Eval_Button_ID, "Evaluate");
    NextPage_Button =
        new wxButton(this, Enum::OF_NextPage_Button_ID, "Next Page");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Track_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(RemoveROI_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Optical_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Eval_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(NextPage_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);

    Next_Button->Disable();
    Prev_Button->Disable();
    Track_Button->Disable();
    RemoveROI_Button->Disable();
    Eval_Button->Disable();
    NextPage_Button->Disable();
}

void OpticalFlowPanelButton::OnButton(wxCommandEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    if (e.GetId() == Enum::OF_Next_Button_ID) {
        img_panel->OnButtonIncrement();
    } else if (e.GetId() == Enum::OF_Prev_Button_ID) {
        img_panel->OnButtonDecrement();
    }
}

void OpticalFlowPanelButton::OnKeyPress(wxKeyEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        img_panel->OnButtonIncrement();
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        img_panel->OnButtonDecrement();
    }
}

void OpticalFlowPanelButton::OnToggleTracker(wxCommandEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    // wxMessageBox("OnToggleTracker");
    img_panel->StartTracking();
}

void OpticalFlowPanelButton::OnToggleOpticalFlow(wxCommandEvent &e) {
    Optical_Button->SetLabel("Running");
    Optical_Button->Disable();
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    img_panel->StartOpticalFlow();
    Optical_Button->SetLabel("Done");
    Eval_Button->Enable();
}

void OpticalFlowPanelButton::OnEval(wxCommandEvent &e) {
    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    img_panel->EvalOFResult();
    Eval_Button->Disable();
    Eval_Button->SetLabel("Evaluated");
    NextPage_Button->Enable();
}

void OpticalFlowPanelButton::OnNextPage(wxCommandEvent &e) {
    wxNotebook *notebook = (wxNotebook *)FindWindowById(Enum::NOTEBOOK_ID);
    int current_page = notebook->GetSelection();
    if (current_page < notebook->GetPageCount() - 1) {
        notebook->SetSelection(current_page + 1);
    } else {
        wxMessageBox("This is the last page");
    }
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanelButton, wxPanel)
EVT_BUTTON(Enum::OF_NextPage_Button_ID, OpticalFlowPanelButton::OnNextPage)
EVT_BUTTON(Enum::OF_Eval_Button_ID, OpticalFlowPanelButton::OnEval)
EVT_BUTTON(Enum::OF_Optical_Button_ID, OpticalFlowPanelButton::OnToggleOpticalFlow)
EVT_BUTTON(Enum::OF_Track_Button_ID, OpticalFlowPanelButton::OnToggleTracker)
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

