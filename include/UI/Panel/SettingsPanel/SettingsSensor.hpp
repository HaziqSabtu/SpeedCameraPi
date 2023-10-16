#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

#define DSPS Data::Settings::Panel::Sensor

class SettingsSensorComponent : public SettingsComponent {
  public:
    SettingsSensorComponent(wxWindow *parent);

    void setValue(const SensorConfig &config);
    SensorConfig getValue();

  private:
    const STD WidthTD = DSPS::WidthTD;
    const STDV WidthDD = DSPS::WidthDD;
    const SCDD WidthCtrlData = DSPS::WidthCtrlData;

    const STD FocalLengthTD = DSPS::FocalLengthTD;
    const STDV FocalLengthDD = DSPS::FocalLengthDD;
    const SCDD FocalLengthCtrlData = DSPS::FocalLengthCtrlData;

    SettingsChildComponentDouble *width;
    SettingsChildComponentDouble *focalLength;
};
