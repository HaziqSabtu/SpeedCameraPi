#pragma once

#include <wx/wx.h>

#include <UI/Data/InfoData.hpp>
#include <UI/Panel/Common/Spacer.hpp>
#include <UI/StaticText/Hyperlink.hpp>
#include <Utils/wxUtils.hpp>

/**
 * @brief The info panel
 * @image html infopanel.png
 * @image latex infopanel.png
 */
class InfoPanel : public wxPanel {
  public:
    InfoPanel(wxWindow *parent, wxWindowID id);
    ~InfoPanel();

  private:
    wxBoxSizer *mainSizer;
};