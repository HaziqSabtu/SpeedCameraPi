#pragma once

#include <UI/Control/ButtonControl/ButtonControl.hpp>
#include <UI/Control/SpinControl/SpinControl.hpp>

#include <UI/StaticText/DefaultStaticText.hpp>

#include <UI/Theme/SettingsData.hpp>

#include <Utils/Config/ConfigStruct.hpp>

#include <wx/wx.h>

class SettingsComponent : public wxPanel {
  public:
    SettingsComponent(wxWindow *parent, const StaticTextData &textData,
                      const std::vector<StaticTextData> &descriptionData);

  protected:
    wxSizer *mainSizer;
};

class SettingsChildComponent : public wxPanel {
  public:
    SettingsChildComponent(wxWindow *parent, const StaticTextData &textData,
                           const std::vector<StaticTextData> &descriptionData);

  protected:
    wxSizer *mainSizer;
};

class SettingsChildComponentInt : public SettingsChildComponent {
  public:
    SettingsChildComponentInt(
        wxWindow *parent, const StaticTextData &textData,
        const std::vector<StaticTextData> &descriptionData);

    SpinControlInt *getControl() { return control; }

  private:
    SpinControlInt *control;
};

class SettingsChildComponentDouble : public SettingsChildComponent {
  public:
    SettingsChildComponentDouble(
        wxWindow *parent, const StaticTextData &textData,
        const std::vector<StaticTextData> &descriptionData);

    SpinControlDouble *getControl() { return control; }

  private:
    SpinControlDouble *control;
};

class SettingsChildComponentBool : public SettingsChildComponent {
  public:
    SettingsChildComponentBool(
        wxWindow *parent, const StaticTextData &textData,
        const std::vector<StaticTextData> &descriptionData);

    ButtonControl *getControl() { return control; }

  private:
    ButtonControl *control;
};