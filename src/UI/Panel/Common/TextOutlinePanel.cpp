#include <UI/Panel/Common/TextOutlinePanel.hpp>
#include <cmath>
#include <iostream>
#include <wx/gdicmn.h>
#include <wx/gtk/colour.h>
#include <wx/gtk/stattext.h>
#include <wx/settings.h>

TextOutlinePanel::TextOutlinePanel(wxWindow *parent, wxString text)
    : wxPanel(parent, wxID_ANY), text(text) {
    outlineColor = wxColour(29, 161, 242); // Default outline color is red
    outlineWidth = 3;

    offset = round(outlineWidth / 2);

    // m_button = new wxButton(this, wxID_ANY, "Click me!");
    // m_button2 = new wxButton(this, wxID_ANY, "Click me2!");

    int topPaddingSize =
        textSize + round(static_cast<double>(outlineWidth) / 2);

    topPadding = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                                  wxSize(topPaddingSize, topPaddingSize));
    // new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(17, 17));
    // spacer->SetBackgroundColour(wxColour(255, 0, 255));
    bottomPadding = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                                     wxSize(outlineWidth, outlineWidth));
    // spacer2->SetBackgroundColour(wxColour(255, 0, 255));

    leftPadding = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                                   wxSize(outlineWidth, outlineWidth));
    // vspacer->SetBackgroundColour(wxColour(0, 255, 255));
    rightPadding = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition,
                                    wxSize(outlineWidth, outlineWidth));
    // vspacer2->SetBackgroundColour(wxColour(0, 255, 255));

    Bind(wxEVT_PAINT, &TextOutlinePanel::OnPaint, this);
}

void TextOutlinePanel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    wxPen outlinePen(outlineColor, outlineWidth, wxPENSTYLE_SOLID);
    dc.SetPen(outlinePen);

    wxSize textSize = dc.GetTextExtent(text);

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

    dc.DrawText(text, textX, textY);
}

void TextOutlinePanel::SetOutlineColor(const wxColour &color) {
    outlineColor = color;
    Refresh();
}

void TextOutlinePanel::SetOutlineWidth(int width) {
    outlineWidth = width;
    Refresh();
}

void TextOutlinePanel::SetText(const wxString &text) {
    this->text = text;
    Refresh();
}

// clang-format off
wxBEGIN_EVENT_TABLE(TextOutlinePanel, wxPanel) 
EVT_PAINT(TextOutlinePanel::OnPaint) 
wxEND_EVENT_TABLE()