#pragma once

#include "UI/Data/Theme.hpp"
#include "UI/StaticText/RichText.hpp"
#include <wx/wx.h>

namespace RTC = RichTextCollection;

class TextOutlinePanel : public wxPanel {
  public:
    TextOutlinePanel(wxWindow *parent, RTD textData);
    void SetOutlineColor(const wxColour &color);
    void SetOutlineWidth(int width);
    void SetTextData(const RTD &textData);
    void SetButtonSizer(wxSizer *sizer);

  protected:
    // TODO: Add this to theme
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

    RTD textData = RTC::CALIB_NONE;

    wxBoxSizer *hSizer;
    wxBoxSizer *vSizer;

    void OnPaint(wxPaintEvent &event);

    wxDECLARE_EVENT_TABLE();
};
