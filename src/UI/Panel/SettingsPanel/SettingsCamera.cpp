#include <UI/Panel/SettingsPanel/SettingsCamera.hpp>

SettingsCameraComponent::SettingsCameraComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPC::Title, DSPC::Description) {
    id = new SettingsChildComponentInt(this, IDTD, IDDD);
    id->getControl()->setSpinData(IDCtrlData);

    width = new SettingsChildComponentInt(this, WidthTD, WidthDD);
    width->getControl()->setSpinData(WidthCtrlData);

    height = new SettingsChildComponentInt(this, HeightTD, HeightDD);
    height->getControl()->setSpinData(HeightCtrlData);

    fps = new SettingsChildComponentInt(this, FPSTD, FPSDD);
    fps->getControl()->setSpinData(FPSCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(id, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(width, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(height, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(fps, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsCameraComponent::setValue(const CameraConfig &config) {
    id->getControl()->setValue(config.Camera_ID);
    width->getControl()->setValue(config.Camera_Width);
    height->getControl()->setValue(config.Camera_Height);
    fps->getControl()->setValue(config.Camera_FPS);
}

CameraConfig SettingsCameraComponent::getValue() {
    auto i = id->getControl()->getValue();
    auto w = width->getControl()->getValue();
    auto h = height->getControl()->getValue();
    auto f = fps->getControl()->getValue();

    CameraConfig config;
    config.Camera_ID = i;
    config.Camera_Width = w;
    config.Camera_Height = h;
    config.Camera_FPS = f;
    return config;
}
