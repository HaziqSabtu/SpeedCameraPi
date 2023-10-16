#pragma once

#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

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

    const STD DebugShowImageTD = DSPCap::DebugShowImageTD;
    const STDV DebugShowImageDD = DSPCap::DebugShowImageDD;

    const STD DebugSaveTD = DSPCap::DebugSaveTD;
    const STDV DebugSaveDD = DSPCap::DebugSaveDD;

    SettingsChildComponentInt *maxFrame;
    SettingsChildComponentBool *debugShowImage;
    SettingsChildComponentBool *debugSave;
};
