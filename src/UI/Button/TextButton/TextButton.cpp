#include <UI/Button/TextButton/TextButton.hpp>
#include <wx/font.h>

TextButton::TextButton(wxWindow *parent, wxWindowID id,
                       const TextButtonData &data)
    : wxPanel(parent, wxID_ANY) {
    sizer = new wxBoxSizer(wxVERTICAL);

    button = new wxButton(this, id, data.text, wxDefaultPosition, data.size);
    button->SetBackgroundColour(data.bgColor);
    button->SetForegroundColour(data.fgColor);

    wxFontInfo fontInfo(20);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Bold();
    wxFont font(fontInfo);

    button->SetFont(font);

    sizer->Add(button, 1, wxEXPAND);

    SetSizer(sizer);
    Layout();
}