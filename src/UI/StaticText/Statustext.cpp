#include <UI/StaticText/Statustext.hpp>

StatusText::StatusText(wxWindow *parent, wxWindowID id, wxString text)
    : wxStaticText(parent, id, text) {

    SetBackgroundColour(backgroundColour);
    SetForegroundColour(textColour);

    wxFontInfo fontInfo(18);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto");
    wxFont font(fontInfo);

    SetFont(font);

    text_sizer = new wxBoxSizer(wxVERTICAL);
    text_sizer->AddStretchSpacer();
    text_sizer->Add(this, 0, wxEXPAND);
    text_sizer->AddStretchSpacer();
}

StatusText::~StatusText() {}

void StatusText::SetText(wxString text) { SetLabelText(text); }
