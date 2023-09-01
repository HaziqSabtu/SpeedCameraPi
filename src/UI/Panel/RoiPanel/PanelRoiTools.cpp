#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/PanelRoiTools.hpp>

RoiButtonTools::RoiButtonTools(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_TOOLS) {

    Ok_button = new BitmapOK(this, Enum::RO_AcceptRect_Button_ID);
    Remove_button = new BitmapRemove(this, Enum::RO_RemoveRect_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Ok_button, 1, wxEXPAND);
    buttonSizer->Add(Remove_button, 1, wxEXPAND);

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
}

void RoiButtonTools::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void RoiButtonTools::update(const AppState &state) {
    // set panel
    RoiPanelState ps = state.roiPanel;

    setPanelState(ps.roiToolsStatusState);

    Ok_button->update(ps.acceptRoiButtonState);
    Remove_button->update(ps.clearRoiButtonState);
}

void RoiButtonTools::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_HIDDEN) {
        this->Hide();
        return;
    }

    if (state == PanelState::PANEL_OK) {
        this->Show();
        return;
    }

    throw std::runtime_error("Invalid panel state");
}
