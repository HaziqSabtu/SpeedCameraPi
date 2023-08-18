#pragma once

#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

#define DSPCap Data::Settings::Panel::Capture

class SettingsCaptureComponent : public SettingsComponent {
  public:
    SettingsCaptureComponent(wxWindow *parent);

    void setValue(const CaptureConfig &config);
    CaptureConfig getValue();

  private:
    const STD MaxFrameTD = DSPCap::MaxFrameTD;
    const STDV MaxFrameDD = DSPCap::MaxFrameDD;
    const SCDI MaxFrameCtrlData = DSPCap::MaxFrameCtrlData;

    const STD DebugTD = DSPCap::DebugTD;
    const STDV DebugDD = DSPCap::DebugDD;

    SettingsChildComponentInt *maxFrame;
    SettingsChildComponentBool *debug;
};
