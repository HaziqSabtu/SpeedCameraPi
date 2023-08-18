#include "UI/Control/ButtonControl/ButtonControl.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>
#include <wx/font.h>
#include <wx/gtk/colour.h>

SettingsComponent::SettingsComponent(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : wxPanel(parent) {

    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *titleText = new DefaultStaticText(this, wxID_ANY, textData);
    mainSizer->Add(titleText, 0, wxBOTTOM, 0);

    for (auto &t : descriptionData) {
        wxStaticText *descriptionText =
            new DefaultStaticText(this, wxID_ANY, t);
        mainSizer->Add(descriptionText, 0, wxBOTTOM, 0);
    }

    SetSizer(mainSizer);
}

SettingsChildComponent::SettingsChildComponent(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : wxPanel(parent) {
    mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *titleText = new DefaultStaticText(this, wxID_ANY, textData);
    mainSizer->Add(titleText, 0, wxBOTTOM, 0);

    for (auto &t : descriptionData) {
        wxStaticText *descriptionText =
            new DefaultStaticText(this, wxID_ANY, t);
        mainSizer->Add(descriptionText, 0, wxBOTTOM, 0);
    }

    SetSizer(mainSizer);
}

SettingsChildComponentInt::SettingsChildComponentInt(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : SettingsChildComponent(parent, textData, descriptionData) {
    control = new SpinControl<int>(this, wxID_ANY, 0);
    mainSizer->AddSpacer(10);
    mainSizer->Add(control, 1, wxEXPAND, 0);
}

SettingsChildComponentDouble::SettingsChildComponentDouble(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : SettingsChildComponent(parent, textData, descriptionData) {
    control = new SpinControl<double>(this, wxID_ANY, 0);
    mainSizer->AddSpacer(10);
    mainSizer->Add(control, 1, wxEXPAND, 0);
}

SettingsChildComponentBool::SettingsChildComponentBool(
    wxWindow *parent, const StaticTextData &textData,
    const std::vector<StaticTextData> &descriptionData)
    : SettingsChildComponent(parent, textData, descriptionData) {
    control = new ButtonControl(this, wxID_ANY);
    mainSizer->AddSpacer(10);
    mainSizer->Add(control, 1, wxEXPAND, 0);
}
