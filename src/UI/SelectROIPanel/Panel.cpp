#include <UI/SelectROI/Panel.hpp>

SelectRoiPanel::SelectRoiPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {

    std::string filePath = "C:/Users/kakik/Desktop/P1/data/bin/car7_768F.bin";
    FILEWR::ReadFile(filePath, imgData);

    button_panel = new SelectRoiPanelButton(this, Enum::BUTTON_PANEL_ID,
                                            Enum::IMG_PANEL_ID);

    img_panel = new SelectRoiPanelImage(this, Enum::IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

// clang-format off
BEGIN_EVENT_TABLE(SelectRoiPanel, wxPanel)
END_EVENT_TABLE()
