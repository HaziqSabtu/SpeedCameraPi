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

    const STD ObjectHeightTD = DSPMes::ObjectHeightTD;
    const STDV ObjectHeightDD = DSPMes::ObjectHeightDD;
    const SCDI ObjectHeightCtrlData = DSPMes::ObjectHeightCtrlData;

    void laneSizeButtonHandler(wxCommandEvent &e);
    void matSizeButtonHandler(wxCommandEvent &e);

    SettingsChildComponentInt *objectWidth;
    SettingsChildComponentInt *objectHeight;

    wxButton *laneSizeButton;
    wxButton *matSizeButton;
    wxButton *matSizeButton2;

    // in mm
    const int LANE_WIDTH = 3500;
    const int MAT_WIDTH = 420;
};
