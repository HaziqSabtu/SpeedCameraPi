#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

#define DSPMes Data::Settings::Panel::Measurement

class SettingsMeasurementComponent : public SettingsComponent {
  public:
    SettingsMeasurementComponent(wxWindow *parent);

    void setValue(const MeasurementConfig &config);
    MeasurementConfig getValue();

  private:
    const STD ObjectWidthTD = DSPMes::ObjectWidthTD;
    const STDV ObjectWidthDD = DSPMes::ObjectWidthDD;
    const SCDI ObjectWidthCtrlData = DSPMes::ObjectWidthCtrlData;

    void laneSizeButtonHandler(wxCommandEvent &e);
    void matSizeButtonHandler(wxCommandEvent &e);

    SettingsChildComponentInt *objectWidth;

    wxButton *laneSizeButton;
    wxButton *matSizeButton;

    // in mm
    const int LANE_WIDTH = 3500;
    const int MAT_WIDTH = 380;
};
