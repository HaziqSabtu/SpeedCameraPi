#pragma once

#include <wx/wx.h>

#include <UI/Data/InfoData.hpp>
#include <UI/Panel/Common/Spacer.hpp>
#include <UI/StaticText/Hyperlink.hpp>
#include <Utils/wxUtils.hpp>

class InfoPanel : public wxPanel {
  public:
    InfoPanel(wxWindow *parent, wxWindowID id);
    ~InfoPanel();

  private:
    wxBoxSizer *mainSizer;
};