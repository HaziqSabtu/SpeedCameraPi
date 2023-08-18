#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

#define DSPOpt Data::Settings::Panel::OpticalFlow

class SettingsOptFlowComponent : public SettingsComponent {
  public:
    SettingsOptFlowComponent(wxWindow *parent);

    void setValue(const OpticalFlowConfig &config);
    OpticalFlowConfig getValue();

  private:
    const STD MaxCornersTD = DSPOpt::MaxCornersTD;
    const STDV MaxCornersDD = DSPOpt::MaxCornersDD;
    const SCDI MaxCornersCtrlData = DSPOpt::MaxCornersCtrlData;

    const STD QualityLevelTD = DSPOpt::QualityLevelTD;
    const STDV QualityLevelDD = DSPOpt::QualityLevelDD;
    const SCDD QualityLevelCtrlData = DSPOpt::QualityLevelCtrlData;

    const STD MinDistanceTD = DSPOpt::MinDistanceTD;
    const STDV MinDistanceDD = DSPOpt::MinDistanceDD;
    const SCDD MinDistanceCtrlData = DSPOpt::MinDistanceCtrlData;

    const STD BlockSizeTD = DSPOpt::BlockSizeTD;
    const STDV BlockSizeDD = DSPOpt::BlockSizeDD;
    const SCDI BlockSizeCtrlData = DSPOpt::BlockSizeCtrlData;

    const STD UseHarrisDetectorTD = DSPOpt::UseHarrisDetectorTD;
    const STDV UseHarrisDetectorDD = DSPOpt::UseHarrisDetectorDD;

    const STD KTD = DSPOpt::KTD;
    const STDV KDD = DSPOpt::KDD;
    const SCDD KCtrlData = DSPOpt::KCtrlData;

    const STD MinPointDistanceTD = DSPOpt::MinPointDistanceTD;
    const STDV MinPointDistanceDD = DSPOpt::MinPointDistanceDD;
    const SCDD MinPointDistanceCtrlData = DSPOpt::MinPointDistanceCtrlData;

    const STD ThresholdTD = DSPOpt::ThresholdTD;
    const STDV ThresholdDD = DSPOpt::ThresholdDD;
    const SCDD ThresholdCtrlData = DSPOpt::ThresholdCtrlData;

    SettingsChildComponentInt *maxCorners;
    SettingsChildComponentDouble *qualityLevel;
    SettingsChildComponentDouble *minDistance;
    SettingsChildComponentInt *blockSize;
    SettingsChildComponentBool *useHD;
    SettingsChildComponentDouble *k;
    SettingsChildComponentDouble *minPD;
    SettingsChildComponentDouble *threshold;
};
