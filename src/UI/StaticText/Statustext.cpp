#include <UI/StaticText/Statustext.hpp>

StatusText::StatusText(wxWindow *parent, wxWindowID id, wxString text,
                       const wxPoint &pos, const wxSize &size, long style)
    : wxStaticText(parent, id, text, pos, size, style) {

    SetBackgroundColour(backgroundColour);
    SetForegroundColour(textColour);

    wxFontInfo fontInfo(18);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto");
    wxFont font(fontInfo);

    SetFont(font);
}

StatusText::~StatusText() {}

void StatusText::SetText(wxString text) { SetLabelText(text); }
