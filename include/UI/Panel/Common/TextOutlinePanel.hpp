#pragma once

#include "Model/AppState.hpp"
#include "UI/Button/BitmapButton/BitmapButton.hpp"
#include "UI/Data/Theme.hpp"
#include "UI/StaticText/RichText.hpp"
#include <wx/wx.h>

namespace RTC = RichTextCollection;

/**
 * @brief Text outline panel, to group buttons
 * @image html textoutlinepanel.png
 * @image latex textoutlinepanel.png
 *
 */
class TextOutlinePanel : public wxPanel {
  public:
    TextOutlinePanel(wxWindow *parent, RTD textData);
    void SetOutlineColor(const wxColour &color);
    void SetOutlineWidth(int width);
    void SetTextData(const RTD &textData);
    void SetButtonSizer(wxSizer *sizer);

  protected:
    wxColour defaultBackgroundColor = Theme::Primary60;
    wxColour outlineColor = Theme::Accent10;
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
