#include "SelectroiPanel.hpp"

SelectRoiPanel::SelectRoiPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    std::string filePath = "C:/Users/kakik/Desktop/P1/data/bin/car7_768F.bin";
    FILEWR::ReadFile(filePath, imgData);
    cv::Mat firstImg = imgData[count].image;

    // Create Button Panel and Buttons
    button_panel = new wxPanel(this);
    Next_Button = new wxButton(button_panel, Next_Button_ID, "Next");
    Prev_Button = new wxButton(button_panel, Prev_Button_ID, "Prev");
    Sel_Button = new wxButton(button_panel, Sel_Button_ID, "Select");
    RemoveROI_Button =
        new wxButton(button_panel, RemoveROI_Button_ID, "Remove ROI");

    // Create the button sizer
    button_sizer = new wxBoxSizer(wxHORIZONTAL);
    button_sizer->Add(Next_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Prev_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(Sel_Button, 0, wxALL | wxCENTER, 5);
    button_sizer->Add(RemoveROI_Button, 0, wxALL | wxCENTER, 5);
    button_panel->SetSizer(button_sizer);

    // Create the image panel
    img_panel = new wxPanel(this);
    // img_panel->SetSize(500, 500);
    img_bitmap = new BufferedBitmap(img_panel, wxID_ANY);
    img_bitmap->SetImage(firstImg);

    img_sizer = new wxBoxSizer(wxHORIZONTAL);
    img_sizer->Add(img_bitmap, 0);
    wxSize img_panel_size = img_panel->GetClientSize();
    img_panel->SetSizer(img_sizer);
    // img_bitmap->SetSize(img_panel_size);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND | wxALL, 5);
    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void SelectRoiPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Next_Button_ID) {
        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    } else if (e.GetId() == Prev_Button_ID) {
        count = (count <= 0) ? 0 : count - 1;
    } else if (e.GetId() == Sel_Button_ID) {
        // todo set selected IMG
    }
    img_bitmap->SetImage(imgData[count].image);
}

void SelectRoiPanel::OnKeyPress(wxKeyEvent &e) {
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        count = (count <= 0) ? 0 : count - 1;
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        // todo set selected IMG
    }
    img_bitmap->SetImage(imgData[count].image);
}

void SelectRoiPanel::OnToggleROI(wxCommandEvent &e) {
    // check if img_panel2 is hidden
    // if (img_panel2->IsShown()) {
    //     isROISelect = !isROISelect;
    // }
    img_bitmap->SetImage(imgData[count].image);
    img_bitmap->RemoveRectangle();
}

// void SelectRoiPanel::OnSize(wxSizeEvent &e) {
//     wxSize img_panel_size = GetClientSize();
//     img_bitmap->SetClientSize(img_panel_size);
// }

// clang-format off
BEGIN_EVENT_TABLE(SelectRoiPanel, wxPanel)
EVT_BUTTON(RemoveROI_Button_ID, SelectRoiPanel::OnToggleROI)
EVT_BUTTON(wxID_ANY, SelectRoiPanel::OnButton)
EVT_KEY_DOWN(SelectRoiPanel::OnKeyPress)
// EVT_SIZE(SelectRoiPanel::OnSize)
END_EVENT_TABLE()
