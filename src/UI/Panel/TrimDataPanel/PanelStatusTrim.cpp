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
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/TrimDataPanel/PanelStatusTrim.hpp>

TrimButtonMain::TrimButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::TRIM_DATA) {

    Start_Button = new BitmapT2Calibration(this, Enum::TD_Start_Button_ID);
    Preview_Button = new BitmapReplay(this, Enum::TD_Preview_Button_ID);
    PreviewInThread_Button = new BitmapReplay(this, Enum::TD_Range_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Start_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);
    buttonSizer->Add(PreviewInThread_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void TrimButtonMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void TrimButtonMain::update(const AppState &state) {
    // set panel
    TrimDataPanelState ps = state.trimDataPanel;

    Start_Button->update(ps.startButtonState);
    Preview_Button->update(ps.replayButtonState);
    PreviewInThread_Button->update(ps.rangeButtonState);
}
