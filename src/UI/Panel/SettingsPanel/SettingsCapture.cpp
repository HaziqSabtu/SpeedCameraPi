#include <UI/Panel/SettingsPanel/SettingsCapture.hpp>

SettingsCaptureComponent::SettingsCaptureComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPCap::Title, DSPCap::Description) {
    maxFrame = new SettingsChildComponentInt(this, MaxFrameTD, MaxFrameDD);

    maxFrame->getControl()->setSpinData(MaxFrameCtrlData);

    debug = new SettingsChildComponentBool(this, DebugTD, DebugDD);

    mainSizer->AddSpacer(20);
    mainSizer->Add(maxFrame, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(debug, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsCaptureComponent::setValue(const CaptureConfig &config) {
    maxFrame->getControl()->setValue(config.maxFrame);
    debug->getControl()->setValue(config.Debug);
}

CaptureConfig SettingsCaptureComponent::getValue() {
    auto mf = maxFrame->getControl()->getValue();
    auto d = debug->getControl()->getValue();

    CaptureConfig c;
    c.maxFrame = mf;
    c.Debug = d;
    return c;
}
