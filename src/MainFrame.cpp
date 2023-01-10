#include "MainFrame.hpp"

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title) {
    // Create the Next_Button panel
    std::string filePath = "C:/Users/kakik/Desktop/P1/data/bin/car7_768F.bin";
    FILEWR::ReadFile(filePath, imgData);
    cv::Mat firstImg = imgData[count].image;

    // Create Button Panel and Buttons
    button_panel = new wxPanel(this);
    Next_Button = new wxButton(button_panel, Next_Button_ID, "Next");
    Prev_Button = new wxButton(button_panel, Prev_Button_ID, "Prev");
    Sel_Button = new wxButton(button_panel, Sel_Button_ID, "Select");
    Frame_Button = new wxButton(button_panel, Frame_Button_ID, "Frame Change");
    RemoveROI_Button =
        new wxButton(button_panel, RemoveROI_Button_ID, "Remove ROI");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Sel_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Frame_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(RemoveROI_Button, 0, wxALL | wxCENTER, 5);
    button_panel->SetSizer(button_sizer);

    // Create the image panel
    img_panel = new wxPanel(this);
    img_bitmap = new BufferedBitmap(img_panel, wxID_ANY);
    img_bitmap->SetImage(firstImg);

    img_panel2 = new wxPanel(this);
    img_bitmap2 = new BufferedBitmap(img_panel2, wxID_ANY);
    img_bitmap2->SetImage(firstImg);

    img_sizer = new wxBoxSizer(wxHORIZONTAL);
    img_sizer->Add(img_bitmap, 0);
    img_panel->SetSizer(img_sizer);

    img_sizer2 = new wxBoxSizer(wxHORIZONTAL);
    img_sizer2->Add(img_bitmap2, 0);
    img_panel2->SetSizer(img_sizer2);

    // Set the main sizer for the frame
    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);
    main_sizer->Add(img_panel2, 1, wxEXPAND);
    SetSizer(main_sizer);
    Fit();

    img_panel->Show();
    img_panel2->Hide();

    SetFocus();
}

void MainFrame::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Next_Button_ID) {
        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    } else if (e.GetId() == Prev_Button_ID) {
        count = (count <= 0) ? 0 : count - 1;
    } else if (e.GetId() == Sel_Button_ID) {
        img_bitmap2->SetImage(imgData[count].image);
    }
    img_bitmap->SetImage(imgData[count].image);
}

void MainFrame::OnKeyPress(wxKeyEvent &e) {
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        count = (count <= 0) ? 0 : count - 1;
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        img_bitmap2->SetImage(imgData[count].image);
    }
    img_bitmap->SetImage(imgData[count].image);
}

void MainFrame::OnSwitchPanel(wxCommandEvent &e) {
    if (img_panel->IsShown()) {
        img_panel->Hide();
        img_panel2->Show();
    } else {
        img_panel2->Hide();
        img_panel->Show();
    }
    // Tell the sizer to adjust the size and position of the widgets based on
    // the current layout rules
    main_sizer->Layout();
    this->Refresh();
}
void MainFrame::OnToggleROI(wxCommandEvent &e) {
    // check if img_panel2 is hidden
    // if (img_panel2->IsShown()) {
    //     isROISelect = !isROISelect;
    // }
    img_bitmap->SetImage(imgData[count].image);
    img_bitmap->RemoveRectangle();
}

// clang-format off
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(Frame_Button_ID, MainFrame::OnSwitchPanel)
EVT_BUTTON(RemoveROI_Button_ID, MainFrame::OnToggleROI)
EVT_BUTTON(wxID_ANY, MainFrame::OnButton)
EVT_KEY_DOWN(MainFrame::OnKeyPress)
END_EVENT_TABLE()
