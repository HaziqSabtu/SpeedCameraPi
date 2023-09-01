#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Replay.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Box.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Lanes.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Ruler.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ResultPanel/PanelResultPreview.hpp>

ResultPanelPreview::ResultPanelPreview(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RESULT_NONE) {

    Box_Button = new BitmapT2Box(this, Enum::RE_Box_Button_ID);
    Intersection_Button = new BitmapT2Ruler(this, Enum::RE_Lines_Button_ID);
    Lanes_Button = new BitmapT2Lanes(this, Enum::RE_Lanes_Button_ID);
    Replay_Button = new BitmapReplay(this, Enum::RE_Replay_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Box_Button, 1, wxEXPAND);
    buttonSizer->Add(Intersection_Button, 1, wxEXPAND);
    buttonSizer->Add(Lanes_Button, 1, wxEXPAND);
    buttonSizer->Add(Replay_Button, 1, wxEXPAND);

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

void ResultPanelPreview::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void ResultPanelPreview::update(const AppState &state) {
    // set panel
    ResultPanelState ps = state.resultPanel;
    setPanelState(ps.previewStatusState);

    Box_Button->update(ps.boxButtonState);
    Intersection_Button->update(ps.linesButtonState);
    Lanes_Button->update(ps.lanesButtonState);
    Replay_Button->update(ps.replayButtonState);
}

void ResultPanelPreview::setPanelState(PanelState state) {
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
