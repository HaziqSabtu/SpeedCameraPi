#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ResultPanel/PanelStatusResult.hpp>

ResultPanelMain::ResultPanelMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RESULT_NONE) {

    Process_Button = new BitmapCalibration(this, Enum::RE_Start_Button_ID);
    Redundant_Button =
        new BitmapCalibration(this, Enum::RE_Redundant_Button_ID);
    Preview_Button = new BitmapT2MagnifyGlass(this, Enum::RE_Preview_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Process_Button, 1, wxEXPAND);
    buttonSizer->Add(Redundant_Button, 1, wxEXPAND);
    buttonSizer->Add(Preview_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void ResultPanelMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void ResultPanelMain::update(const AppState &state) {
    // set panel
    ResultPanelState ps = state.resultPanel;
    setPanelState(ps.state);

    Process_Button->update(ps.resultButtonState);
    Redundant_Button->update(ps.redundantButtonState);
    Preview_Button->update(ps.previewButtonState);
}

void ResultPanelMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::RESULT_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::RESULT_NONE);
    }
}
