#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

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
