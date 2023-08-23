#pragma once

#pragma once

#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Panel/SettingsPanel/SettingsComponent.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include "Utils/Config/ConfigStruct.hpp"
#include <UI/Theme/SettingsData.hpp>
#include <wx/gtk/spinbutt.h>
#include <wx/sizer.h>

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

    SettingsChildComponentBool *autoManualCalibration;
    SettingsChildComponentBool *autoCalibration;
    SettingsChildComponentBool *autoRoi;
};
