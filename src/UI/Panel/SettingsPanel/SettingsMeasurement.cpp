#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Panel/SettingsPanel/SettingsMeasurement.hpp>
#include <wx/dlimpexp.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>

SettingsMeasurementComponent::SettingsMeasurementComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPMes::Title, DSPMes::Description) {

    objectWidth =
        new SettingsChildComponentInt(this, ObjectWidthTD, ObjectWidthDD);
    objectWidth->getControl()->setSpinData(ObjectWidthCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(objectWidth, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsMeasurementComponent::setValue(const MeasurementConfig &config) {
    objectWidth->getControl()->setValue(config.ObjectWidth);
}

MeasurementConfig SettingsMeasurementComponent::getValue() {
    auto ow = objectWidth->getControl()->getValue();

    MeasurementConfig c;
    c.ObjectWidth = ow;
    return c;
}
