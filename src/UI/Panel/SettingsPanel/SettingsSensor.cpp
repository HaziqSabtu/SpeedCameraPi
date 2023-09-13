#include <UI/Panel/SettingsPanel/SettingsSensor.hpp>

SettingsSensorComponent::SettingsSensorComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPS::Title, DSPS::Description) {

    width = new SettingsChildComponentDouble(this, WidthTD, WidthDD);
    width->getControl()->setSpinData(WidthCtrlData);

    focalLength =
        new SettingsChildComponentDouble(this, FocalLengthTD, FocalLengthDD);
    focalLength->getControl()->setSpinData(FocalLengthCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(width, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(focalLength, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsSensorComponent::setValue(const SensorConfig &config) {
    width->getControl()->setValue(config.SensorWidth);
    focalLength->getControl()->setValue(config.SensorFocalLength);
}

SensorConfig SettingsSensorComponent::getValue() {
    auto sw = width->getControl()->getValue();
    auto sfl = focalLength->getControl()->getValue();

    SensorConfig c;
    c.SensorWidth = sw;
    c.SensorFocalLength = sfl;
    return c;
}