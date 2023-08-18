#pragma once

#include "UI/Control/ButtonControl/ButtonControl.hpp"
#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Font/Font.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include <wx/colour.h>
#include <wx/spinctrl.h>
#include <wx/wx.h>

const FontData titleFontData = {"Roboto", 20, FontStyle::FONT_BOLD};
const FontData titleFontData2 = {"Roboto", 13, FontStyle::FONT_BOLD};
const FontData descriptionFontData = {"Roboto", 10, FontStyle::FONT_LIGHT};

const StaticTextData tData = {wxColour(0, 0, 0), wxTransparentColour,
                              "SETTINGS COMPONENT", titleFontData};

const StaticTextData tData2 = {wxColour(0, 0, 0), wxTransparentColour,
                               "SETTINGS CHILD COMPONENT", titleFontData2};

const StaticTextData dData = {wxColour(0, 0, 0), wxTransparentColour,
                              "This is a settings component",
                              descriptionFontData};

const std::vector<StaticTextData> textDataVector = {dData, dData, dData};
const std::vector<StaticTextData> textDataVector2 = {dData, dData, dData,
                                                     dData};

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