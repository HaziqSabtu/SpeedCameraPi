#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/PanelStatusMain.hpp>

RoiButtonMain::RoiButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_NONE) {

    Roi_Button = new BitmapT2Calibration(this, Enum::RO_Calibration_Button_ID);
    Preview_Button = new BitmapT2MagnifyGlass(this, Enum::RO_Preview_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::RO_Remove_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Roi_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);

    Reset_Button->Bind(wxEVT_BUTTON, &RoiButtonMain::OnButtonClicked, this);
}

void RoiButtonMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void RoiButtonMain::update(const AppState &state) {
    // set panel
    RoiPanelState ps = state.roiPanel;
    setPanelState(ps.state);

    Roi_Button->update(ps.roiButtonState);
    Preview_Button->update(ps.cameraButtonState);
    Reset_Button->update(ps.removeButtonState);
}

void RoiButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::ROI_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::ROI_NONE);
    }
}
