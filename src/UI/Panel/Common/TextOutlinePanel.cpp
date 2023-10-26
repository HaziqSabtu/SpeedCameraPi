#include "Model/AppState.hpp"
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

/**
 * @brief Construct a new Text Outline Panel:: Text Outline Panel object
 *
 * @param parent Pointer to parent window
 * @param textData Text data
 */
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

/**
 * @brief Handle paint event
 *
 * @param event Event
 */
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

/**
 * @brief Set the outline color
 *
 * @param color Color
 */
void TextOutlinePanel::SetOutlineColor(const wxColour &color) {
    outlineColor = color;
    Refresh();
}

/**
 * @brief Set the outline width
 *
 * @param width Width
 */
void TextOutlinePanel::SetOutlineWidth(int width) {
    outlineWidth = width;
    Refresh();
}

/**
 * @brief Set the text data
 *
 * @param textData Text data
 */
void TextOutlinePanel::SetTextData(const RTD &textData) {
    this->textData = textData;
    Refresh();
}

/**
 * @brief Set the button sizer
 *
 * @param sizer Sizer
 */
void TextOutlinePanel::SetButtonSizer(wxSizer *sizer) {
    vSizer = new wxBoxSizer(wxVERTICAL);
    vSizer->Add(topPadding, 0, wxEXPAND);
    vSizer->Add(sizer, 0, wxEXPAND | wxALL, 10);
    vSizer->Add(bottomPadding, 0, wxEXPAND);

    hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(leftPadding, 0, wxEXPAND);
    hSizer->Add(vSizer, 1, wxEXPAND);
    hSizer->Add(rightPadding, 0, wxEXPAND);

    SetSizer(hSizer);
    Fit();
}

// clang-format off
wxBEGIN_EVENT_TABLE(TextOutlinePanel, wxPanel) 
EVT_PAINT(TextOutlinePanel::OnPaint) 
wxEND_EVENT_TABLE()