#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/ResultPanel/PanelStatusResult.hpp>

ResultMainStatusPanel::ResultMainStatusPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::RESULT_NONE) {

    calibrate_Button = new BitmapCalibration(this, Enum::RE_Start_Button_ID);
    camera_Button = new BitmapT2MagnifyGlass(this, Enum::RE_Preview_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(calibrate_Button, 1, wxEXPAND);
    buttonSizer->Add(camera_Button, 1, wxEXPAND);

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

void ResultMainStatusPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void ResultMainStatusPanel::update(const AppState &state) {
    // set panel
    ResultPanelState ps = state.resultPanel;
    setPanelState(ps.state);

    calibrate_Button->update(ps.resultButtonState);
    camera_Button->update(ps.previewButtonState);
}

void ResultMainStatusPanel::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::ROI_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::ROI_NONE);
    }
}