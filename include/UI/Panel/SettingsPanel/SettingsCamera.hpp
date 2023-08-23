#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

#define DSPC Data::Settings::Panel::Camera

class SettingsCameraComponent : public SettingsComponent {
  public:
    SettingsCameraComponent(wxWindow *parent);

    void setValue(const CameraConfig &config);
    CameraConfig getValue();

  private:
    const STD IDTD = DSPC::IDTD;
    const STDV IDDD = DSPC::IDDD;
    const SCDI IDCtrlData = DSPC::IDCtrlData;

    const STD WidthTD = DSPC::WidthTD;
    const STDV WidthDD = DSPC::WidthDD;
    const SCDI WidthCtrlData = DSPC::WidthCtrlData;

    const STD HeightTD = DSPC::HeightTD;
    const STDV HeightDD = DSPC::HeightDD;
    const SCDI HeightCtrlData = DSPC::HeightCtrlData;

    const STD FPSTD = DSPC::FPSTD;
    const STDV FPSDD = DSPC::FPSDD;
    const SCDI FPSCtrlData = DSPC::FPSCtrlData;

    SettingsChildComponentInt *id;
    SettingsChildComponentInt *width;
    SettingsChildComponentInt *height;
    SettingsChildComponentInt *fps;
};