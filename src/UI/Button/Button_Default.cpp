#include <UI/Button/Button_Default.hpp>

DefaultButton::DefaultButton(wxWindow *parent, wxWindowID id,
                             const wxString &label, const wxPoint &pos,
                             const wxSize &size, long style,
                             const wxValidator &validator, const wxString &name)
    : wxButton(parent, id, label, pos, size, style, validator, name) {
    SetBackgroundColour(background);
    SetForegroundColour(foreground);
}

DefaultButton::~DefaultButton() {}