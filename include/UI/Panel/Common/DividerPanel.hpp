#pragma once

#include <wx/wx.h>

class DividerPanel : public wxPanel {
  public:
    DividerPanel(wxWindow *parent);
    void SetLineColor(const wxColour &color);

  private:
    wxColour m_lineColor;

    void OnPaint(wxPaintEvent &event);

    wxDECLARE_EVENT_TABLE();
};
