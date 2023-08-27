#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

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
