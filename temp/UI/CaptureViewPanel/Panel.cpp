#include <UI/CaptureViewPanel/Panel.hpp>

CaptureViewPanel::CaptureViewPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    button_panel = new CaptureViewPanelButton(this, Enum::CV_BUTTON_PANEL_ID);

    img_bitmap = new ImageBitmap(this, Enum::CV_IMG_PANEL_ID);
    img_bitmap->Bind(wxEVT_SIZE, &CaptureViewPanel::OnSize, this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);

    SetSize(800, 600);
    Center();
};

CaptureViewPanel::~CaptureViewPanel() {}

void CaptureViewPanel::OnIncrement() {
    c = (c >= imgData.size() - 1) ? imgData.size() - 1 : c + 1;
    img_bitmap->SetImage(imgData[c].image);
}

void CaptureViewPanel::OnDecrement() {
    c = (c <= 0) ? 0 : c - 1;
    img_bitmap->SetImage(imgData[c].image);
}

void CaptureViewPanel::OnPageChange() {
    CameraPanel *p_Camera =
        dynamic_cast<CameraPanel *>(GetParent()->FindWindow(Enum::CP_Panel_ID));
    if (p_Camera != NULL) {
        imgData = p_Camera->GetImgData();
        img_bitmap->SetImage(imgData[c].image);
        for (int i = 1; i < imgData.size(); i++) {
            double timediff = imgData[i].TimeDiff(imgData[i - 1]);
            wxLogMessage("Time diff: %f", timediff);
        }
    } else {
        wxLogMessage("CameraPanel not found");
    }
}

void CaptureViewPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CaptureViewPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CV_Next_Button_ID) {
        OnIncrement();
    }

    if (e.GetId() == Enum::CV_Prev_Button_ID) {
        OnDecrement();
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CaptureViewPanel, wxPanel) 
EVT_BUTTON(wxID_ANY, CaptureViewPanel::OnButton)
wxEND_EVENT_TABLE()
