#include <UI/SelectLinePanel/Panel.hpp>

SelectLinePanel::SelectLinePanel(wxWindow *parent, wxWindowID id,
                                 std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel = new SelectLinePanelButton(this, Enum::SL_BUTTON_PANEL_ID);

    img_panel = new SelectLinePanelImage(this, Enum::SL_IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void SelectLinePanel::OnButton(wxCommandEvent &e) {

    if (e.GetId() == Enum::SL_Canny_Button_ID) {
        img_panel->OnCanny();
        button_panel->OnCanny();
    }

    if (e.GetId() == Enum::SL_Hough_Button_ID) {
        img_panel->OnHough();
        button_panel->OnHough();
    }

    if (e.GetId() == Enum::SL_Clear_Button_ID) {
        img_panel->OnClear();
    }
}
// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanel, wxPanel)
    EVT_BUTTON(wxID_ANY, SelectLinePanel::OnButton)
END_EVENT_TABLE()
