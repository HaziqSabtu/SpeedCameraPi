#include "UI/Panel/CapturePanel/PanelStatusTools.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Reset.hpp"
#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_Trim.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"

CaptureButtonTools::CaptureButtonTools(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CAPTURE_TOOLS) {

    Save_Button =
        new BitmapSave(this, Enum::CP_Save_Button_ID, Data::BitmapSaveData);
    Trim_Button = new BitmapTrim(this, Enum::CP_Trim_Button_ID);
    Reset_Button = new BitmapReset(this, Enum::CP_Reset_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Save_Button, 1, wxEXPAND);
    buttonSizer->Add(Trim_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CaptureButtonTools::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonTools::update(const AppState &state) {
    auto ps = state.capturePanel;
    setPanelState(ps.toolsStatusState);

    Save_Button->update(ps.saveButtonState);
    Trim_Button->update(ps.trimButtonState);
    Reset_Button->update(ps.resetButtonState);
}

void CaptureButtonTools::setPanelState(PanelState state) {
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