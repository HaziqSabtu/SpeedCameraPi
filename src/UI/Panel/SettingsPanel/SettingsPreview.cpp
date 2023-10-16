#include <UI/Panel/SettingsPanel/SettingsPreview.hpp>

SettingsPreviewComponent::SettingsPreviewComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPPrv::Title, DSPPrv::Description) {

    width = new SettingsChildComponentInt(this, WidthTD, WidthDD);
    width->getControl()->setSpinData(WidthCtrlData);

    height = new SettingsChildComponentInt(this, HeightTD, HeightDD);
    height->getControl()->setSpinData(HeightCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(width, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(height, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    SetSizer(mainSizer);
}

void SettingsPreviewComponent::setValue(const PreviewConfig &config) {
    width->getControl()->setValue(config.width);
    height->getControl()->setValue(config.height);
}

PreviewConfig SettingsPreviewComponent::getValue() {
    auto w = width->getControl()->getValue();
    auto h = height->getControl()->getValue();

    PreviewConfig c;
    c.width = w;
    c.height = h;
    return c;
}
