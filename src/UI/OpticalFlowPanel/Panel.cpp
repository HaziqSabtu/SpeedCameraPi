#include <UI/OpticalFlowPanel/Panel.hpp>

OpticalFlowPanel::OpticalFlowPanel(wxWindow *parent, wxWindowID id,
                                   std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel = new OpticalFlowPanelButton(this, Enum::OF_BUTTON_PANEL_ID);
    img_panel = new OpticalFlowPanelImage(this, Enum::OF_IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void OpticalFlowPanel::OnPageChange() {
    SelectRoiPanelImage *img_panel_roi = dynamic_cast<SelectRoiPanelImage *>(
        GetParent()->FindWindow(Enum::SR_IMG_PANEL_ID));

    int count = img_panel_roi->GetCount();
    img_panel->SetCount(count);

    cv::Rect r = img_panel_roi->GetTrueRect();
    img_panel->SetTrueRect(r);
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanel, wxPanel)
END_EVENT_TABLE()
