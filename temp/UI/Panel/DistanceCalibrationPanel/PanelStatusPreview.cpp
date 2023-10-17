#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/DistanceCalibrationPanel/PanelStatusPreview.hpp>

HorizontalCalibrationButtonPreview::HorizontalCalibrationButtonPreview(
    wxWindow *parent)
    : TextOutlinePanel(parent, RTC::PREVIEW) {
    // TODO: Remove this
    // PreviewCamera_Button = new BitmapT2Camera(this, Enum::DC_Preview_Button_ID);
    // PreviewCapture_Button =
    //     new BitmapT2MagnifyGlass(this, Enum::DC_PreviewCapture_Button_ID);

    // buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    // buttonSizer->Add(PreviewCamera_Button, 1, wxEXPAND);
    // buttonSizer->Add(PreviewCapture_Button, 1, wxEXPAND);

    // SetButtonSizer(buttonSizer);
}

void HorizontalCalibrationButtonPreview::update(const AppState &state) {
    // set panel
    DistanceCalibrationPanelState ps = state.distanceCalibrationPanel;

    // setPanelState(ps.previewStatusState);

    // PreviewCamera_Button->update(ps.previewButtonState);
    // PreviewCapture_Button->update(ps.prevCaptureButtonState);
}

void HorizontalCalibrationButtonPreview::setPanelState(PanelState state) {
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