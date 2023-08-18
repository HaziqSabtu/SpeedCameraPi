#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

#define DSPPrv Data::Settings::Panel::Preview

class SettingsPreviewComponent : public SettingsComponent {
  public:
    SettingsPreviewComponent(wxWindow *parent);

    void setValue(const PreviewConfig &config);
    PreviewConfig getValue();

  private:
    const STD WidthTD = DSPPrv::WidthTD;
    const STDV WidthDD = DSPPrv::WidthDD;
    const SCDI WidthCtrlData = DSPPrv::WidthCtrlData;

    const STD HeightTD = DSPPrv::HeightTD;
    const STDV HeightDD = DSPPrv::HeightDD;
    const SCDI HeightCtrlData = DSPPrv::HeightCtrlData;

    SettingsChildComponentInt *width;
    SettingsChildComponentInt *height;
};
