#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Panel/SettingsPanel/SettingsRansac.hpp>
#include <wx/dlimpexp.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>

SettingsRansacComponent::SettingsRansacComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPRan::Title, DSPRan::Description) {

    threshold =
        new SettingsChildComponentDouble(this, ThresholdTD, ThresholdDD);
    threshold->getControl()->setSpinData(ThresholdCtrlData);

    minPoints = new SettingsChildComponentInt(this, MinPointsTD, MinPointsDD);
    minPoints->getControl()->setSpinData(MinPointsCtrlData);

    maxIterations =
        new SettingsChildComponentInt(this, MaxIterationsTD, MaxIterationsDD);
    maxIterations->getControl()->setSpinData(MaxIterationsCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(threshold, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(minPoints, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(maxIterations, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
                   10);

    SetSizer(mainSizer);
}

void SettingsRansacComponent::setValue(const RansacConfig &config) {
    threshold->getControl()->setValue(config.threshold);
    minPoints->getControl()->setValue(config.minPoints);
    maxIterations->getControl()->setValue(config.maxIterations);
}

RansacConfig SettingsRansacComponent::getValue() {
    RansacConfig config;
    config.threshold = threshold->getControl()->getValue();
    config.minPoints = minPoints->getControl()->getValue();
    config.maxIterations = maxIterations->getControl()->getValue();
    return config;
}
