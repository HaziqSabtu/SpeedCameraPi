#pragma once

#include "UI/Theme/Theme.hpp"
#include <wx/wx.h>

class TextOutlinePanel : public wxPanel {
  public:
    TextOutlinePanel(wxWindow *parent, wxString text);
    void SetOutlineColor(const wxColour &color);
    void SetOutlineWidth(int width);
    void SetText(const wxString &text);

  protected:
    wxColour defaultBackgroundColor = Theme::Background;

    wxColour outlineColor = Theme::Primary;
    int outlineWidth = 3;

    wxColour textColor = Theme::Text;

    const int textSize = 11;
    int offset;
    int rectRadius = 5;
    int textOffsetX = 5;
    int textOffsetY = 1;

    wxStaticText *topPadding;
    wxStaticText *bottomPadding;
    wxStaticText *leftPadding;
    wxStaticText *rightPadding;

    wxString text;

    void OnPaint(wxPaintEvent &event);

    wxDECLARE_EVENT_TABLE();
};
