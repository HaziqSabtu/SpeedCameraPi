#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Panel/SettingsPanel/SettingsPanel.hpp>

SettingsScrollPanel::SettingsScrollPanel(wxWindow *parent)
    : wxScrolledWindow(parent, wxID_ANY) {
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    AppConfig c;

    settingsCameraComponent = new SettingsCameraComponent(this);
    settingsCameraComponent->setValue(c.GetCameraConfig());

    mainSizer->Add(settingsCameraComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsSensorComponent = new SettingsSensorComponent(this);
    settingsSensorComponent->setValue(c.GetSensorConfig());

    mainSizer->Add(settingsSensorComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsCaptureComponent = new SettingsCaptureComponent(this);
    settingsCaptureComponent->setValue(c.GetCaptureConfig());

    mainSizer->Add(settingsCaptureComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsModelComponent = new SettingsModelComponent(this);
    settingsModelComponent->setValue(c.GetModelConfig());

    mainSizer->Add(settingsModelComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsOptFlowComponent = new SettingsOptFlowComponent(this);
    settingsOptFlowComponent->setValue(c.GetOpticalFlowConfig());

    mainSizer->Add(settingsOptFlowComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsMeasurementComponent = new SettingsMeasurementComponent(this);
    settingsMeasurementComponent->setValue(c.GetMeasurementConfig());

    mainSizer->Add(settingsMeasurementComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsPreviewComponent = new SettingsPreviewComponent(this);
    settingsPreviewComponent->setValue(c.GetPreviewConfig());

    mainSizer->Add(settingsPreviewComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsRansacComponent = new SettingsRansacComponent(this);
    settingsRansacComponent->setValue(c.GetRansacConfig());

    mainSizer->Add(settingsRansacComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsBlueHSVComponent = new SettingsBlueHSVComponent(this);
    settingsBlueHSVComponent->setValue(c.GetBlueRange());

    mainSizer->Add(settingsBlueHSVComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    settingsYellowHSVComponent = new SettingsYellowHSVComponent(this);
    settingsYellowHSVComponent->setValue(c.GetYellowRange());

    mainSizer->Add(settingsYellowHSVComponent, 0, wxEXPAND | wxALL, 5);
    mainSizer->AddSpacer(20);

    SetSizer(mainSizer);
    FitInside();

    SetScrollRate(0, 5);
};

SettingsModel SettingsScrollPanel::getSettingsModel() {
    SettingsModel s;

    s.cameraConfig = settingsCameraComponent->getValue();
    s.sensorConfig = settingsSensorComponent->getValue();
    s.captureConfig = settingsCaptureComponent->getValue();
    s.modelConfig = settingsModelComponent->getValue();
    s.opticalFlowConfig = settingsOptFlowComponent->getValue();
    s.measurementConfig = settingsMeasurementComponent->getValue();
    s.previewConfig = settingsPreviewComponent->getValue();
    s.ransacConfig = settingsRansacComponent->getValue();
    s.blueRange = settingsBlueHSVComponent->getValue();
    s.yellowRange = settingsYellowHSVComponent->getValue();

    return s;
}

void SettingsScrollPanel::setSettingsModel(const SettingsModel &s) {
    settingsCameraComponent->setValue(s.cameraConfig);
    settingsSensorComponent->setValue(s.sensorConfig);
    settingsCaptureComponent->setValue(s.captureConfig);
    settingsModelComponent->setValue(s.modelConfig);
    settingsOptFlowComponent->setValue(s.opticalFlowConfig);
    settingsMeasurementComponent->setValue(s.measurementConfig);
    settingsPreviewComponent->setValue(s.previewConfig);
    settingsRansacComponent->setValue(s.ransacConfig);
    settingsBlueHSVComponent->setValue(s.blueRange);
    settingsYellowHSVComponent->setValue(s.yellowRange);
}
