#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

#define DSPRan Data::Settings::Panel::Ransac

class SettingsRansacComponent : public SettingsComponent {
  public:
    SettingsRansacComponent(wxWindow *parent);

    void setValue(const RansacConfig &config);
    RansacConfig getValue();

  private:
    const STD ThresholdTD = DSPRan::ThresholdTD;
    const STDV ThresholdDD = DSPRan::ThresholdDD;
    const SCDD ThresholdCtrlData = DSPRan::ThresholdCtrlData;

    const STD MinPointsTD = DSPRan::MinPointsTD;
    const STDV MinPointsDD = DSPRan::MinPointsDD;
    const SCDI MinPointsCtrlData = DSPRan::MinPointsCtrlData;

    const STD MaxIterationsTD = DSPRan::MaxIterationsTD;
    const STDV MaxIterationsDD = DSPRan::MaxIterationsDD;
    const SCDI MaxIterationsCtrlData = DSPRan::MaxIterationsCtrlData;

    SettingsChildComponentDouble *threshold;
    SettingsChildComponentInt *minPoints;
    SettingsChildComponentInt *maxIterations;
};
