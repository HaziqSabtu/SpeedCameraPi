#pragma once

#include <wx/wx.h>

class TextOutlinePanel : public wxPanel {
  public:
    TextOutlinePanel(wxWindow *parent, wxString text);
    void SetOutlineColor(const wxColour &color);
    void SetOutlineWidth(int width);
    void SetText(const wxString &text);

  protected:
    wxColour defaultBackgroundColor = wxColour(240, 240, 240);

    wxColour outlineColor;
    int outlineWidth;

    const int textSize = 11;
    int offset;
    int rectRadius = 5;
    int textOffsetX = 5;
    int textOffsetY = 1;

    // wxButton *m_button;
    // wxButton *m_button2;

    wxStaticText *topPadding;
    wxStaticText *bottomPadding;
    wxStaticText *leftPadding;
    wxStaticText *rightPadding;

    wxString text;

    void OnPaint(wxPaintEvent &event);

    wxDECLARE_EVENT_TABLE();
};
