#include "UI/Button/BitmapButton/Button_Capture.hpp"
#include "UI/Button/BitmapButton/Button_Load.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Replay.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/PanelStatusMain.hpp>
#include <wx/gdicmn.h>
#include <wx/gtk/bmpbuttn.h>
#include <wx/gtk/stattext.h>
#include <wx/sizer.h>

CaptureButtonMain::CaptureButtonMain(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::CAPTURE_NONE) {

    Capture_Button = new BitmapCapture(this, Enum::CP_Capture_Button_ID);
    Load_Button = new BitmapLoad(this, Enum::CP_Load_Button_ID);
    Replay_Button = new BitmapReplay(this, Enum::CP_Replay_Button_ID);
    Reset_Button = new BitmapRemove(this, Enum::CP_ClearCapture_Button_ID);
    Camera_Button = new BitmapT2Camera(this, Enum::CP_ToggleCamera_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(Capture_Button, 1, wxEXPAND);
    buttonSizer->Add(Load_Button, 1, wxEXPAND);
    buttonSizer->Add(Camera_Button, 1, wxEXPAND);
    buttonSizer->Add(Replay_Button, 1, wxEXPAND);
    buttonSizer->Add(Reset_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void CaptureButtonMain::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void CaptureButtonMain::setPanelState(PanelState state) {
    if (state == PanelState::PANEL_OK) {
        SetTextData(RTC::CAPTURE_OK);
    }

    if (state == PanelState::PANEL_NOT_OK) {
        SetTextData(RTC::CAPTURE_NONE);
    }
}

void CaptureButtonMain::update(const AppState &state) {
    setPanelState(state.capturePanel.captureStatusState);
    Capture_Button->update(state.capturePanel.captureButtonState);
    Load_Button->update(state.capturePanel.loadButtonState);
    Replay_Button->update(state.capturePanel.replayButtonState);
    Reset_Button->update(state.capturePanel.removeButtonState);
    Camera_Button->update(state.capturePanel.cameraButtonState);
}
