#include <UI/Panel/Common/TextOutlinePanel.hpp>
#include <cmath>
#include <iostream>
#include <wx/colour.h>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/gtk/colour.h>
#include <wx/gtk/stattext.h>
#include <wx/settings.h>
#include <wx/stringimpl.h>

TextOutlinePanel::TextOutlinePanel(wxWindow *parent, RTD textData)
    : wxPanel(parent, wxID_ANY), textData(textData) {

    offset = round(outlineWidth / 2);

    int topPaddingSize =
        textSize + round(static_cast<double>(outlineWidth) / 2);

    topPadding =
        new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                         wxSize(topPaddingSize, topPaddingSize));
    bottomPadding =
        new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                         wxSize(outlineWidth, outlineWidth));
    leftPadding =
        new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                         wxSize(outlineWidth, outlineWidth));
    rightPadding =
        new wxStaticText(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                         wxSize(outlineWidth, outlineWidth));

    Bind(wxEVT_PAINT, &TextOutlinePanel::OnPaint, this);
}

void TextOutlinePanel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    wxPen outlinePen(outlineColor, outlineWidth, wxPENSTYLE_SOLID);
    dc.SetPen(outlinePen);

    wxFontInfo fontInfo;
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Bold();
    wxFont font(fontInfo);

    dc.SetFont(font);

    wxSize textSize;
    for (auto t : textData) {
        textSize.IncBy(dc.GetTextExtent(t.text).GetWidth(),
                       textSize.GetHeight() == 0
                           ? dc.GetTextExtent(t.text).GetHeight()
                           : 0);
    }
    int textX = 0;
    int textY = 0;

    wxBrush brush(wxTransparentColour);
    dc.SetBrush(brush);

    int startRectX = textX + offset;
    int startRectY = textY + (textSize.GetHeight() / 2);
    int rectWidth = size.GetWidth() - startRectX - 1;
    int rectHeight = size.GetHeight() - startRectY - 1;
    dc.DrawRoundedRectangle(startRectX, startRectY, rectWidth, rectHeight,
                            rectRadius);

    dc.SetPen(wxPen(wxTransparentColour, outlineWidth, wxPENSTYLE_SOLID));

    dc.SetBrush(defaultBackgroundColor);

    int startTextRectX = textX;
    int startTextRectY = textY;
    int textRectWidth = textSize.GetWidth() + textOffsetX;
    int textRectHeight = textSize.GetHeight() + textOffsetY;
    dc.DrawRectangle(startTextRectX, startTextRectY, textRectWidth,
                     textRectHeight);

    dc.SetTextForeground(textColor);

    for (auto t : textData) {

        dc.SetTextForeground(t.colour);
        dc.DrawText(t.text, textX, textY);
        textX += dc.GetTextExtent(t.text).GetWidth();
    }
}

void TextOutlinePanel::SetOutlineColor(const wxColour &color) {
    outlineColor = color;
    Refresh();
}

void TextOutlinePanel::SetOutlineWidth(int width) {
    outlineWidth = width;
    Refresh();
}

void TextOutlinePanel::SetTextData(const RTD &textData) {
    this->textData = textData;
    Refresh();
}

// clang-format off
wxBEGIN_EVENT_TABLE(TextOutlinePanel, wxPanel) 
EVT_PAINT(TextOutlinePanel::OnPaint) 
wxEND_EVENT_TABLE()