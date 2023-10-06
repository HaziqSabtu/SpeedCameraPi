#include "UI/Panel/CapturePanel/PanelStatusROI.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"

CaptureButtonROI::CaptureButtonROI(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_NONE) {

    Roi_Button = new BitmapRoi(this, Enum::CP_Roi_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::CP_RemoveRoi_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Roi_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CaptureButtonROI::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonROI::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::ROI_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::ROI_NONE);
    }
}

void CaptureButtonROI::update(const AppState &state) {
    setPanelState(state.cameraPanel.roiStatusState);
    Roi_Button->update(state.cameraPanel.roiButtonState);
    Reset_Button->update(state.cameraPanel.roiRemoveButtonState);
}