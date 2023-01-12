#include "SelectroiPanel.hpp"

SelectRoiPanel::SelectRoiPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    std::string filePath = "C:/Users/kakik/Desktop/P1/data/bin/car7_768F.bin";
    FILEWR::ReadFile(filePath, imgData);

    SelectRoiPanelButton *button_panel =
        new SelectRoiPanelButton(this, BUTTON_PANEL_ID, IMG_PANEL_ID);

    SelectRoiPanelImage *img_panel =
        new SelectRoiPanelImage(this, IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);
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

void SelectRoiPanel::OnSize(wxSizeEvent &e) {
    wxSize img_panel_size = e.GetSize();

    // get size of img_panel
    // wxSize img_panel_size = img_panel->GetSize();
    // wxSize imgSize = img_panel->GetSize();
    // // wxSize imgSize = img_bitmap->GetSize();
    // img_bitmap->setClientSize(imgSize);
    img_bitmap->SetClientSize(img_panel_size);
    img_panel->SetSize(img_panel_size);
    // Layout();
}

// clang-format off
BEGIN_EVENT_TABLE(SelectRoiPanel, wxPanel)
// EVT_BUTTON(RemoveROI_Button_ID, SelectRoiPanel::OnToggleROI)
// EVT_BUTTON(wxID_ANY, SelectRoiPanel::OnButton)
// EVT_KEY_DOWN(SelectRoiPanel::OnKeyPress)
END_EVENT_TABLE()
