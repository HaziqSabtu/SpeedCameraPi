#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Replay.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Calibration.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/PanelStatusTrim.hpp>

TrimButtonMain::TrimButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::TRIM_DATA) {

    Start_Button = new BitmapT2Calibration(this, Enum::TD_Start_Button_ID);
    Preview_Button = new BitmapReplay(this, Enum::TD_Preview_Button_ID);
    PreviewInThread_Button = new BitmapReplay(this, Enum::TD_Range_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::TD_Reset_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Start_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(PreviewInThread_Button, 1, wxEXPAND);
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

void TrimButtonMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void TrimButtonMain::update(const AppState &state) {
    // set panel
    TrimDataPanelState ps = state.trimDataPanel;

    Start_Button->update(ps.startButtonState);
    Preview_Button->update(ps.replayButtonState);
    PreviewInThread_Button->update(ps.rangeButtonState);
    Reset_Button->update(ps.removeButtonState);
}
