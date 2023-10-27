#include "UI/Panel/Common/Spacer.hpp"
#include <UI/Panel/SettingsPanel/SettingsMeasurement.hpp>
#include <string>

SettingsMeasurementComponent::SettingsMeasurementComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPMes::Title, DSPMes::Description) {

    objectWidth =
        new SettingsChildComponentInt(this, ObjectWidthTD, ObjectWidthDD);
    objectWidth->getControl()->setSpinData(ObjectWidthCtrlData);

    objectHeight =
        new SettingsChildComponentInt(this, ObjectHeightTD, ObjectHeightDD);
    objectHeight->getControl()->setSpinData(ObjectHeightCtrlData);

    laneSizeButton = new wxButton(this, wxID_ANY, std::to_string(LANE_WIDTH),
                                  wxDefaultPosition, wxSize(100, 40));
    matSizeButton = new wxButton(this, wxID_ANY, std::to_string(MAT_WIDTH),
                                 wxDefaultPosition, wxSize(100, 40));

    auto leftSpacer = new Spacer(this);
    auto rightSpacer = new Spacer(this);

    mainSizer->AddSpacer(20);
    mainSizer->Add(objectWidth, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->AddSpacer(10);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(leftSpacer, 1, wxEXPAND);
    buttonSizer->Add(laneSizeButton, 0, wxEXPAND);
    buttonSizer->AddSpacer(10);
    buttonSizer->Add(matSizeButton, 0, wxEXPAND);
    buttonSizer->Add(rightSpacer, 1, wxEXPAND);

    mainSizer->AddSpacer(10);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->AddSpacer(10);
    mainSizer->Add(objectHeight, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);

    laneSizeButton->Bind(wxEVT_BUTTON,
                         &SettingsMeasurementComponent::laneSizeButtonHandler,
                         this);

    matSizeButton->Bind(wxEVT_BUTTON,
                        &SettingsMeasurementComponent::matSizeButtonHandler,
                        this);
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

void SettingsMeasurementComponent::laneSizeButtonHandler(wxCommandEvent &e) {
    objectWidth->getControl()->setValue(LANE_WIDTH);
}

void SettingsMeasurementComponent::matSizeButtonHandler(wxCommandEvent &e) {
    objectWidth->getControl()->setValue(MAT_WIDTH);
}