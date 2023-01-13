#include <UI/SelectROIPanel/ButtonPanel.hpp>

SelectRoiPanelButton::SelectRoiPanelButton(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    // Create Button Panel and Buttons
    Next_Button = new wxButton(this, Enum::SR_Next_Button_ID, "Next");
    Prev_Button = new wxButton(this, Enum::SR_Prev_Button_ID, "Prev");
    Sel_Button = new wxButton(this, Enum::SR_Sel_Button_ID, "Select");
    RemoveROI_Button =
        new wxButton(this, Enum::SR_RemoveROI_Button_ID, "Remove ROI");
    NextPage_Button =
        new wxButton(this, Enum::SR_NextPage_Button_ID, "Next Page");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Sel_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(RemoveROI_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(NextPage_Button, 0, wxALL | wxCENTER, 5);
    this->SetSizer(button_sizer);
}

void SelectRoiPanelButton::OnNextPage(wxCommandEvent &e) {
    // todo next page
    wxNotebook *notebook = (wxNotebook *)FindWindowById(Enum::NOTEBOOK_ID);
    int current_page = notebook->GetSelection();
    if (current_page < notebook->GetPageCount() - 1) {
        notebook->SetSelection(current_page + 1);
    }
    SelectRoiPanelImage *img_panel_roi = dynamic_cast<SelectRoiPanelImage *>(
        GetParent()->FindWindow(Enum::SR_IMG_PANEL_ID));
    int count = img_panel_roi->GetCount();
    // wxMessageBox(std::to_string(count), std::to_string(count),
    //              wxOK | wxICON_INFORMATION);

    OpticalFlowPanelImage *img_panel = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));
    // img_panel->SetCount(count);
}

void SelectRoiPanelButton::OnButton(wxCommandEvent &e) {
    SelectRoiPanelImage *img_panel = dynamic_cast<SelectRoiPanelImage *>(
        GetParent()->FindWindow(Enum::SR_IMG_PANEL_ID));
    if (e.GetId() == Enum::SR_Next_Button_ID) {
        img_panel->OnButtonIncrement();
    } else if (e.GetId() == Enum::SR_Prev_Button_ID) {
        img_panel->OnButtonDecrement();
    } else if (e.GetId() == Enum::SR_Sel_Button_ID) {
        // todo set selected IMG
    } else if (e.GetId() == Enum::SR_RemoveROI_Button_ID) {
        // todo remove ROI
        wxMessageBox("Remove ROI", "Remove ROI", wxOK | wxICON_INFORMATION);
    }
}

void SelectRoiPanelButton::OnKeyPress(wxKeyEvent &e) {
    SelectRoiPanelImage *img_panel = dynamic_cast<SelectRoiPanelImage *>(
        GetParent()->FindWindow(Enum::SR_IMG_PANEL_ID));
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        img_panel->OnButtonIncrement();
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        img_panel->OnButtonDecrement();
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        // todo set selected IMG
    }
}

// clang-format off
BEGIN_EVENT_TABLE(SelectRoiPanelButton, wxPanel)
EVT_BUTTON(Enum::SR_NextPage_Button_ID, SelectRoiPanelButton::OnNextPage)
EVT_BUTTON(wxID_ANY, SelectRoiPanelButton::OnButton)
EVT_KEY_DOWN(SelectRoiPanelButton::OnKeyPress)
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

