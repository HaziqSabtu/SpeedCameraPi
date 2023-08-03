#include <UI/Button/Button_Default.hpp>
#include <wx/font.h>

DefaultButton::DefaultButton(wxWindow *parent, wxWindowID id,
                             const wxString &label, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : wxButton(parent, id, label, pos, size, style, validator, name) {
    SetBackgroundColour(background);
    SetForegroundColour(foreground);

    wxFontInfo fontInfo;
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Light();
    wxFont font(fontInfo);

    SetFont(font);
}

DefaultButton::DefaultButton(wxWindow *parent, wxWindowID id,
                             const wxString &label, const wxColour &background,
                             const wxColour &foreground, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : wxButton(parent, id, label, pos, size, style, validator, name),
      background(background), foreground(foreground) {
    SetBackgroundColour(background);
    SetForegroundColour(foreground);

    wxFontInfo fontInfo;
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto");
    wxFont font(fontInfo);

    SetFont(font);
}

DefaultButton::~DefaultButton() {}