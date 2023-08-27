#include <UI/Panel/SettingsPanel/SettingsThreads.hpp>

SettingsThreadsComponent::SettingsThreadsComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPThd::Title, DSPThd::Description) {

    autoManualCalibration = new SettingsChildComponentBool(
        this, AutoManualCalibrationTD, AutoManualCalibrationDD);

    autoCalibration = new SettingsChildComponentBool(this, AutoCalibrationTD,
                                                     AutoCalibrationDD);

    autoRoi = new SettingsChildComponentBool(this, AutoRoiTD, AutoRoiDD);

    mainSizer->AddSpacer(20);
    mainSizer->Add(autoCalibration, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
                   10);
    mainSizer->Add(autoManualCalibration, 0,
                   wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(autoRoi, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsThreadsComponent::setValue(const ThreadsConfig &config) {
    autoManualCalibration->getControl()->setValue(config.autoManualCalibration);
    autoCalibration->getControl()->setValue(config.autoCalibration);
    autoRoi->getControl()->setValue(config.autoRoi);
}

ThreadsConfig SettingsThreadsComponent::getValue() {
    auto amc = autoManualCalibration->getControl()->getValue();
    auto ac = autoCalibration->getControl()->getValue();
    auto ar = autoRoi->getControl()->getValue();

    ThreadsConfig c;
    c.autoManualCalibration = amc;
    c.autoCalibration = ac;
    c.autoRoi = ar;
    return c;
}
