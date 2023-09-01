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

void CaptureButtonTools::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonTools::update(const AppState &state) {
    Save_Button->update(state.cameraPanel.saveButtonState);
    Trim_Button->update(state.cameraPanel.trimButtonState);
    Reset_Button->update(state.cameraPanel.resetButtonState);
}