#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

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
