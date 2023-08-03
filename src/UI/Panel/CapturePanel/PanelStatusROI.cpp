#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"

ROIStatusPanel::ROIStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_NONE) {

    roi_Button = new BitmapRoi(this, Enum::CP_ChangeRoi_Button_ID);
    reset_Button = new BitmapRemove(this, wxID_ANY);

    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(roi_Button, 1, wxEXPAND);
    hSizer->Add(reset_Button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(hSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
}

void ROIStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void ROIStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::ROI_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::ROI_NONE);
    }
}

void ROIStatusPanel::update(const AppState &state) {
    setPanelState(state.cameraPanel.roiStatusState);
    roi_Button->update(state.cameraPanel.roiButtonState);
    reset_Button->update(state.cameraPanel.roiRemoveButtonState);
}