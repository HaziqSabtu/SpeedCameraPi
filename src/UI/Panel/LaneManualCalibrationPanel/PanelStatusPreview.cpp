#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/LaneManualCalibrationPanel/PanelStatusPreview.hpp>

LaneManualCalibrationButtonPreview::LaneManualCalibrationButtonPreview(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::PREVIEW) {

    PreviewCamera_Button = new BitmapT2Camera(this, Enum::LM_Preview_Button_ID);
    // PreviewCapture_Button =
    //     new BitmapT2MagnifyGlass(this, Enum::LM_PreviewCapture_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(PreviewCamera_Button, 1, wxEXPAND);
    buttonSizer->Add(PreviewCapture_Button, 1, wxEXPAND);

    SetButtonSizer(buttonSizer);
}

void LaneManualCalibrationButtonPreview::update(const AppState &state) {
    // set panel
    // ManualCalibrationPanelState ps = state.laneManualCalibrationPanel;

    // setPanelState(ps.previewStatusState);

    // PreviewCamera_Button->update(ps.previewButtonState);
    // PreviewCapture_Button->update(ps.prevCaptureButtonState);
}

void LaneManualCalibrationButtonPreview::setPanelState(PanelState state) {
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