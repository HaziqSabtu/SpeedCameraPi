#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/PanelStatusRoi.hpp>

RoiMainStatusPanel::RoiMainStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_NONE) {

    calibrate_Button =
        new BitmapT2Calibration(this, Enum::RO_Calibration_Button_ID);
    camera_Button = new BitmapT2MagnifyGlass(this, Enum::RO_Preview_Button_ID);
    reset_Button = new BitmapRemove(this, Enum::RO_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(camera_Button, 1, wxEXPAND);
    buttonSizer->Add(reset_Button, 1, wxEXPAND);

    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();

    reset_Button->Bind(wxEVT_BUTTON, &RoiMainStatusPanel::OnButtonClicked,
                       this);
}

void RoiMainStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void RoiMainStatusPanel::update(const AppState &state) {
    // set panel
    RoiPanelState ps = state.roiPanel;
    setPanelState(ps.state);

    calibrate_Button->update(ps.roiButtonState);
    camera_Button->update(ps.cameraButtonState);
    reset_Button->update(ps.removeButtonState);
}

void RoiMainStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::ROI_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::ROI_NONE);
    }
}
