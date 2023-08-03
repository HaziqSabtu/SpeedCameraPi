#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Button/BitmapButton/Bitmap_Calibration.hpp"
#include "UI/Button/BitmapButton/Button_OK.hpp"
#include "UI/Button/BitmapButton/Button_Preview.hpp"
#include "UI/Button/BitmapButton/Button_Remove.hpp"
#include "UI/Button/BitmapButton/Button_Stop.hpp"
#include "UI/Button/BitmapButton/Type2/Button_Camera.hpp"
#include "UI/Button/BitmapButton/Type2/Button_MagnifyGlass.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include "UI/StaticText/RichText.hpp"
#include "UI/Theme/Data.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/RoiPanel/PanelRoiTools.hpp>

RoiToolsPanel::RoiToolsPanel(wxWindow *parent)
    : TextOutlinePanel(parent, RTC::ROI_TOOLS) {

    ok_button = new BitmapOK(this, Enum::RO_AcceptRect_Button_ID);
    remove_button = new BitmapRemove(this, Enum::RO_RemoveRect_Button_ID);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(ok_button, 1, wxEXPAND);
    buttonSizer->Add(remove_button, 1, wxEXPAND);

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

void RoiToolsPanel::OnButtonClicked(wxCommandEvent &e) { e.Skip(); }

void RoiToolsPanel::update(const AppState &state) {
    // set panel
    // ManualCalibrationPanelState ps = state.manualCalibrationPanel;
    // setPanelState(ps.state);

    // calibrate_Button->update(ps.calibrationButtonState);
    // stop_Button->update(ps.stopButtonState);
    // camera_Button->update(ps.cameraButtonState);
    // reset_Button->update(ps.removeButtonState);
}
