#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Button/Button_Default.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "Utils/Enum.hpp"

ROIStatusPanel::ROIStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_NONE) {

    roi_Button = new BitmapRoi(this, wxID_ANY);
    reset_Button = new BitmapRemove(this, wxID_ANY);

    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(roi_Button, 1, wxEXPAND);
    hSizer->Add(reset_Button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    // vSizer->Add(roi_Button, 0, wxEXPAND | wxTOP | wxRIGHT | wxLEFT, 10);
    // vSizer->Add(reset_Button, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(hSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();

    // reset_Button->Bind(wxEVT_BUTTON, &ROIStatusPanel::OnButtonClicked, this);
}

void ROIStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }
