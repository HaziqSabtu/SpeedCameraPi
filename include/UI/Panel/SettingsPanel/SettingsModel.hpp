#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

#define DSPMod Data::Settings::Panel::Model

class SettingsModelComponent : public SettingsComponent {
  public:
    SettingsModelComponent(wxWindow *parent);

    void setValue(const ModelConfig &config);
    ModelConfig getValue();

  private:
    const STD MaxPoolTD = DSPMod::MaxPoolTD;
    const STDV MaxPoolDD = DSPMod::MaxPoolDD;
    const SCDI MaxPoolCtrlData = DSPMod::MaxPoolCtrlData;

    SettingsChildComponentInt *maxPool;
};
