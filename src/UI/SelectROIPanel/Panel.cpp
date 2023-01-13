#include <UI/SelectROIPanel/Panel.hpp>

SelectRoiPanel::SelectRoiPanel(wxWindow *parent, wxWindowID id,
                               std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel = new SelectRoiPanelButton(this, Enum::SR_BUTTON_PANEL_ID,
                                            Enum::SR_IMG_PANEL_ID);

    img_panel = new SelectRoiPanelImage(this, Enum::SR_IMG_PANEL_ID, imgData);

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
