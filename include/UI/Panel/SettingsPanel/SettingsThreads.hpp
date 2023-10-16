#pragma once

#include <UI/Panel/SettingsPanel/SettingsComponent.hpp>

#define DSPThd Data::Settings::Panel::Threads

class SettingsThreadsComponent : public SettingsComponent {
  public:
    SettingsThreadsComponent(wxWindow *parent);

    void setValue(const ThreadsConfig &config);
    ThreadsConfig getValue();

  private:
    const STD AutoManualCalibrationTD = DSPThd::AutoManualCalibrationTD;
    const STDV AutoManualCalibrationDD = DSPThd::AutoManualCalibrationDD;

    const STD AutoCalibrationTD = DSPThd::AutoCalibrationTD;
    const STDV AutoCalibrationDD = DSPThd::AutoCalibrationDD;

    const STD AutoRoiTD = DSPThd::AutoRoiTD;
    const STDV AutoRoiDD = DSPThd::AutoRoiDD;

    const STD AutoResultTD = DSPThd::AutoResultTD;
    const STDV AutoResultDD = DSPThd::AutoResultDD;

    SettingsChildComponentBool *autoManualCalibration;
    SettingsChildComponentBool *autoCalibration;
    SettingsChildComponentBool *autoRoi;
    SettingsChildComponentBool *autoResult;
};
