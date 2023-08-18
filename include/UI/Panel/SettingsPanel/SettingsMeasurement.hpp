#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

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

    SettingsChildComponentInt *objectWidth;
};
