#include <UI/Panel/SettingsPanel/SettingsHSV.hpp>

SettingsHSVChildComponent::SettingsHSVChildComponent(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : SettingsChildComponent(parent, textData, descriptionData) {
    upperControl = new SpinControl<int>(this, Enum::SE_Upper_HSV_ID, 0);
    upperControl->setText("Upper");

    lowerControl = new SpinControl<int>(this, Enum::SE_Lower_HSV_ID, 0);
    lowerControl->setText("Lower");

    mainSizer->AddSpacer(10);
    mainSizer->Add(upperControl, 1, wxEXPAND, 0);
    mainSizer->AddSpacer(10);
    mainSizer->Add(lowerControl, 1, wxEXPAND, 0);

    Bind(wxEVT_BUTTON, &SettingsHSVChildComponent::OnButton, this, wxID_ANY);
}

void SettingsHSVChildComponent::updateBounds() {
    auto upper = upperControl->getValue();
    auto lower = lowerControl->getValue();

    upperControl->setMinValue(lower);
    lowerControl->setMaxValue(upper);
}

void SettingsHSVChildComponent::OnButton(wxCommandEvent &event) {
    updateBounds();
}

SettingsHSVComponent::SettingsHSVComponent(wxWindow *parent,
                                           const STD &textData,
                                           const STDV &descriptionData)
    : SettingsComponent(parent, textData, descriptionData) {
    hueComponent = new SettingsHSVChildComponent(this, HueTD, HueDD);
    hueComponent->getLowerControl()->setSpinData(HueCtrlData);
    hueComponent->getUpperControl()->setSpinData(HueCtrlData);

    saturationComponent =
        new SettingsHSVChildComponent(this, SaturationTD, SaturationDD);
    saturationComponent->getLowerControl()->setSpinData(SaturationCtrlData);
    saturationComponent->getUpperControl()->setSpinData(SaturationCtrlData);

    valueComponent = new SettingsHSVChildComponent(this, ValueTD, ValueDD);
    valueComponent->getLowerControl()->setSpinData(ValueCtrlData);
    valueComponent->getUpperControl()->setSpinData(ValueCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(hueComponent, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->AddSpacer(10);
    mainSizer->Add(saturationComponent, 0,
                   wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->AddSpacer(10);
    mainSizer->Add(valueComponent, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,
                   10);

    SetSizer(mainSizer);
}

void SettingsHSVComponent::setValue(const HSVRangeConfig &config) {
    hueComponent->getUpperControl()->setValue(config.hueUpper);
    hueComponent->getLowerControl()->setValue(config.hueLower);
    hueComponent->updateBounds();

    saturationComponent->getUpperControl()->setValue(config.saturationUpper);
    saturationComponent->getLowerControl()->setValue(config.saturationLower);
    saturationComponent->updateBounds();

    valueComponent->getUpperControl()->setValue(config.valueUpper);
    valueComponent->getLowerControl()->setValue(config.valueLower);
    valueComponent->updateBounds();
}

HSVRangeConfig SettingsHSVComponent::getValue() {
    auto hueUpper = hueComponent->getUpperControl()->getValue();
    auto hueLower = hueComponent->getLowerControl()->getValue();

    auto saturationUpper = saturationComponent->getUpperControl()->getValue();
    auto saturationLower = saturationComponent->getLowerControl()->getValue();

    auto valueUpper = valueComponent->getUpperControl()->getValue();
    auto valueLower = valueComponent->getLowerControl()->getValue();

    HSVRangeConfig c;
    c.hueUpper = hueUpper;
    c.hueLower = hueLower;
    c.saturationUpper = saturationUpper;
    c.saturationLower = saturationLower;
    c.valueUpper = valueUpper;
    c.valueLower = valueLower;
    return c;
}

SettingsBlueHSVComponent::SettingsBlueHSVComponent(wxWindow *parent)
    : SettingsHSVComponent(parent, DSPHSV::BlueTD, DSPHSV::BlueDD) {}

SettingsYellowHSVComponent::SettingsYellowHSVComponent(wxWindow *parent)
    : SettingsHSVComponent(parent, DSPHSV::YellowTD, DSPHSV::YellowDD) {}
