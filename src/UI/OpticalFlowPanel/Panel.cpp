#include <UI/OpticalFlowPanel/Panel.hpp>

OpticalFlowPanel::OpticalFlowPanel(wxWindow *parent, wxWindowID id,
                                   std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel = new OpticalFlowPanelButton(this, Enum::OF_BUTTON_PANEL_ID,
                                              Enum::OF_IMG_PANEL_ID);

    img_panel = new OpticalFlowPanelImage(this, Enum::OF_IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanel, wxPanel)
END_EVENT_TABLE()
