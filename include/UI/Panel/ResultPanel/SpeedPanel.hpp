#pragma once

#include "Model/AppState.hpp"
#include "UI/Data/Theme.hpp"
#include "UI/StaticText/Statustext.hpp"
#include <wx/gtk/stattext.h>
#include <wx/string.h>
#include <wx/wx.h>

class SpeedPanel : public wxPanel {
  public:
    SpeedPanel(wxWindow *parent);
    ~SpeedPanel();

    void SetSpeed(double speed);

    void update(const AppState &state);

  private:
    StatusText *statusText;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;

    void setPanelState(PanelState state);
};