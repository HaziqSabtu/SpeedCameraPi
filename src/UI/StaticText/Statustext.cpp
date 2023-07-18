#include <UI/StaticText/Statustext.hpp>

StatusText::StatusText(wxWindow *parent, wxWindowID id, wxString text)
    : wxStaticText(parent, id, text) {

    SetBackgroundColour(wxColor(57, 54, 70));
    SetForegroundColour(wxColor(255, 255, 255));
    SetFont(wxFontInfo(20).Bold());

    text_sizer = new wxBoxSizer(wxVERTICAL);
    text_sizer->AddStretchSpacer();
    text_sizer->Add(this, 0, wxEXPAND);
    text_sizer->AddStretchSpacer();
}
