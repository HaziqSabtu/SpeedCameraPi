#include "UI/Panel/CapturePanel/PanelStatusTools.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Reset.hpp"
#include "UI/Button/BitmapButton/Button_Roi.hpp"
#include "UI/Button/BitmapButton/Button_Save.hpp"
#include "UI/Button/BitmapButton/Button_Trim.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"

CaptureToolsPanel::CaptureToolsPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CAPTURE_TOOLS) {

    save_Button =
        new BitmapSave(this, Enum::CP_Save_Button_ID, Data::BitmapSaveData);
    trim_Button = new BitmapTrim(this, Enum::CP_Trim_Button_ID);
    reset_Button = new BitmapReset(this, Enum::CP_Reset_Button_ID);

    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(save_Button, 1, wxEXPAND);
    hSizer->Add(trim_Button, 1, wxEXPAND);
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

void CaptureToolsPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureToolsPanel::update(const AppState &state) {
    save_Button->update(state.cameraPanel.saveButtonState);
    trim_Button->update(state.cameraPanel.trimButtonState);
    reset_Button->update(state.cameraPanel.resetButtonState);
}