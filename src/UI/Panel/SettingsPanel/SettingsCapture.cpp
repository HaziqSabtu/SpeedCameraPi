#include <UI/Panel/SettingsPanel/SettingsCapture.hpp>

SettingsCaptureComponent::SettingsCaptureComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPCap::Title, DSPCap::Description) {
    maxFrame = new SettingsChildComponentInt(this, MaxFrameTD, MaxFrameDD);

    maxFrame->getControl()->setSpinData(MaxFrameCtrlData);

    debugShowImage = new SettingsChildComponentBool(this, DebugShowImageTD,
                                                    DebugShowImageDD);

    debugSave = new SettingsChildComponentBool(this, DebugSaveTD, DebugSaveDD);

    mainSizer->AddSpacer(20);
    mainSizer->Add(maxFrame, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(debugShowImage, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
                   10);
    mainSizer->Add(debugSave, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsCaptureComponent::setValue(const CaptureConfig &config) {
    maxFrame->getControl()->setValue(config.maxFrame);
    debugShowImage->getControl()->setValue(config.DebugShowImage);
    debugSave->getControl()->setValue(config.DebugSave);
}

CaptureConfig SettingsCaptureComponent::getValue() {
    auto mf = maxFrame->getControl()->getValue();
    auto dsi = debugShowImage->getControl()->getValue();
    auto ds = debugSave->getControl()->getValue();

    CaptureConfig c;
    c.maxFrame = mf;
    c.DebugShowImage = dsi;
    c.DebugSave = ds;
    return c;
}
