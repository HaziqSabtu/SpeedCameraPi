#include "UI/Button/BitmapButton/Button_Cancel.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Target.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CalibrationPanel/PanelStatusPreview.hpp>

CalibrationPreviewPanel::CalibrationPreviewPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::PREVIEW) {

    pCamera_button = new BitmapT2Camera(this, Enum::CL_PreviewCamera_Button_ID);
    pCapture_button =
        new BitmapT2MagnifyGlass(this, Enum::CL_PreviewCapture_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(pCamera_button, 1, wxEXPAND);
    buttonSizer->Add(pCapture_button, 1, wxEXPAND);

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

void CalibrationPreviewPanel::update(const AppState &state) {
    // set panel
    CalibrationPanelState ps = state.calibrationPanel;

    setPanelState(ps.previewStatusState);

    pCamera_button->update(ps.prevCameraButtonState);
    pCapture_button->update(ps.prevCaptureButtonState);
}

void CalibrationPreviewPanel::setPanelState(PanelState state) {
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