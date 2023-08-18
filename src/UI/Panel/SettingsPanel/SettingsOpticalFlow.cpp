#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Panel/SettingsPanel/SettingsOpticalFlow.hpp>
#include <wx/dlimpexp.h>
#include <wx/gdicmn.h>
#include <wx/sizer.h>

SettingsOptFlowComponent::SettingsOptFlowComponent(wxWindow *parent)
    : SettingsComponent(parent, DSPOpt::Title, DSPOpt::Description) {

    maxCorners =
        new SettingsChildComponentInt(this, MaxCornersTD, MaxCornersDD);
    maxCorners->getControl()->setSpinData(MaxCornersCtrlData);

    qualityLevel =
        new SettingsChildComponentDouble(this, QualityLevelTD, QualityLevelDD);
    qualityLevel->getControl()->setSpinData(QualityLevelCtrlData);

    minDistance =
        new SettingsChildComponentDouble(this, MinDistanceTD, MinDistanceDD);
    minDistance->getControl()->setSpinData(MinDistanceCtrlData);

    blockSize = new SettingsChildComponentInt(this, BlockSizeTD, BlockSizeDD);
    blockSize->getControl()->setSpinData(BlockSizeCtrlData);

    useHD = new SettingsChildComponentBool(this, UseHarrisDetectorTD,
                                           UseHarrisDetectorDD);

    k = new SettingsChildComponentDouble(this, KTD, KDD);
    k->getControl()->setSpinData(KCtrlData);

    minPD = new SettingsChildComponentDouble(this, MinPointDistanceTD,
                                             MinPointDistanceDD);
    minPD->getControl()->setSpinData(MinPointDistanceCtrlData);

    threshold =
        new SettingsChildComponentDouble(this, ThresholdTD, ThresholdDD);
    threshold->getControl()->setSpinData(ThresholdCtrlData);

    mainSizer->AddSpacer(20);
    mainSizer->Add(maxCorners, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(qualityLevel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(minDistance, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(blockSize, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(useHD, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(k, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(minPD, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(threshold, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void SettingsOptFlowComponent::setValue(const OpticalFlowConfig &config) {
    maxCorners->getControl()->setValue(config.maxCorners);
    qualityLevel->getControl()->setValue(config.qualityLevel);
    minDistance->getControl()->setValue(config.minDistance);
    blockSize->getControl()->setValue(config.blockSize);
    useHD->getControl()->setValue(config.useHarrisDetector);
    k->getControl()->setValue(config.k);
    minPD->getControl()->setValue(config.minPointDistance);
    threshold->getControl()->setValue(config.threshold);
}

OpticalFlowConfig SettingsOptFlowComponent::getValue() {
    auto mc = maxCorners->getControl()->getValue();
    auto ql = qualityLevel->getControl()->getValue();
    auto md = minDistance->getControl()->getValue();
    auto bs = blockSize->getControl()->getValue();
    auto uhd = useHD->getControl()->getValue();
    auto k = this->k->getControl()->getValue();
    auto mpd = minPD->getControl()->getValue();
    auto t = threshold->getControl()->getValue();

    OpticalFlowConfig c;
    c.maxCorners = mc;
    c.qualityLevel = ql;
    c.minDistance = md;
    c.blockSize = bs;
    c.useHarrisDetector = uhd;
    c.k = k;
    c.minPointDistance = mpd;
    c.threshold = t;
    return c;
}
