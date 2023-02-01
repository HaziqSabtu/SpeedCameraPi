#include <UI/ObjectDetectionPanel/Panel.hpp>

ObjectDetectionPanel::ObjectDetectionPanel(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel =
        new ObjectDetectionPanelButton(this, Enum::SR_BUTTON_PANEL_ID);

    img_panel =
        new ObjectDetectionPanelImage(this, Enum::SR_IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void ObjectDetectionPanel::OnButton(wxCommandEvent &e) {
    wxLogMessage("ObjectDetectionPanel::OnButton");
    if (e.GetId() == Enum::OD_Next_Button_ID) {
        img_panel->OnButtonIncrement();
    }
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, ObjectDetectionPanel::OnButton)
END_EVENT_TABLE()
