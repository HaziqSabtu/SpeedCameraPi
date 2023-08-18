#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include <UI/Panel/SettingsPanel/SettingsModel.hpp>
#include <wx/dlimpexp.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>

SettingsModelComponent::SettingsModelComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPMod::Title, DSPMod::Description) {

    maxPool = new SettingsChildComponentInt(this, MaxPoolTD, MaxPoolDD);
    maxPool->getControl()->setSpinData(MaxPoolCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(maxPool, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsModelComponent::setValue(const ModelConfig &config) {
    maxPool->getControl()->setValue(config.Pool_Size);
}

ModelConfig SettingsModelComponent::getValue() {
    auto mp = maxPool->getControl()->getValue();

    ModelConfig c;
    c.Pool_Size = mp;
    return c;
}
