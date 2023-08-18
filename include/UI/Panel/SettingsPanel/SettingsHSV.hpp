#pragma once

#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/wx.h>

#define DSPHSV Data::Settings::Panel::HSV

class SettingsHSVChildComponent : public SettingsChildComponent {
  public:
    SettingsHSVChildComponent(
        wxWindow *parent, const StaticTextData &textData,
        const std::vector<StaticTextData> &descriptionData);

    SpinControlInt *getUpperControl() { return upperControl; }
    SpinControlInt *getLowerControl() { return lowerControl; }

    void updateBounds();

  private:
    SpinControlInt *upperControl;
    SpinControlInt *lowerControl;

  private:
    void OnButton(wxCommandEvent &event);
};

class SettingsHSVComponent : public SettingsComponent {
  public:
    SettingsHSVComponent(wxWindow *parent, const STD &textData,
                         const STDV &descriptionData);

    void setValue(const HSVRangeConfig &config);
    HSVRangeConfig getValue();

    SettingsHSVChildComponent *getHueComponent() { return hueComponent; }
    SettingsHSVChildComponent *getSaturationComponent() {
        return saturationComponent;
    }
    SettingsHSVChildComponent *getValueComponent() { return valueComponent; }

  protected:
    const wxStringPair HueLabels = DSPHSV::HueLabels;
    const wxStringPair SaturationLabels = DSPHSV::SaturationLabels;
    const wxStringPair ValueLabels = DSPHSV::ValueLabels;

    const STD HueTD = DSPHSV::HueTD;
    const STDV HueDD = DSPHSV::HueDD;
    const SCDI HueCtrlData = DSPHSV::HueCtrlData;

    const STD SaturationTD = DSPHSV::SaturationTD;
    const STDV SaturationDD = DSPHSV::SaturationDD;
    const SCDI SaturationCtrlData = DSPHSV::SaturationCtrlData;

    const STD ValueTD = DSPHSV::ValueTD;
    const STDV ValueDD = DSPHSV::ValueDD;
    const SCDI ValueCtrlData = DSPHSV::ValueCtrlData;

    SettingsHSVChildComponent *hueComponent;
    SettingsHSVChildComponent *saturationComponent;
    SettingsHSVChildComponent *valueComponent;

  protected:
};

class SettingsBlueHSVComponent : public SettingsHSVComponent {
  public:
    SettingsBlueHSVComponent(wxWindow *parent);
};

class SettingsYellowHSVComponent : public SettingsHSVComponent {
  public:
    SettingsYellowHSVComponent(wxWindow *parent);
};