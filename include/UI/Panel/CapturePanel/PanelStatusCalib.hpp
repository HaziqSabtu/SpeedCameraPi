#pragma once

#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Panel/Common/TextOutlinePanel.hpp"
#include <Model/AppState.hpp>

class CaptureButtonCalibration : public TextOutlinePanel {
  public:
    CaptureButtonCalibration(wxWindow *parent);

    BitmapButton *Calibrate_Button;
    BitmapButton *Reset_Button;

    void setPanelState(PanelState state);
    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};

class CaptureButtonHorCalibration : public TextOutlinePanel {
  public:
    CaptureButtonHorCalibration(wxWindow *parent);

    BitmapButton *Calibrate_Button;
    BitmapButton *Reset_Button;

    void setPanelState(PanelState state);
    void update(const AppState &state);

  private:
    void OnButtonClicked(wxCommandEvent &e);

    wxBoxSizer *buttonSizer;
};
