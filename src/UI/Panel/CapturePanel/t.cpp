#include "UI/Theme/Theme.hpp"
#include "Utils/Enum.hpp"
#include <UI/Panel/CapturePanel/t.hpp>
#include <stdexcept>
#include <wx/font.h>
#include <wx/gdicmn.h>
#include <wx/gtk/bitmap.h>
#include <wx/gtk/colour.h>

TB::TB(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size,
       long style, const wxString &name)
    : wxPanel(parent, id) {
    hSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer = new wxBoxSizer(wxVERTICAL);

    wxBitmap bit = wxBitmap("noImage_100.png");
    wxSize s = wxSize(50, 50);
    wxBitmap bb = rescale(bit, s);

    wxColour c = Theme::ExitColor;
    normal = recolor(bb, c);

    wxColour d = wxColour(0, 255, 0);
    disabled = recolor(bb, d);

    wxColour e = wxColour(255, 0, 255);
    active = recolor(bb, e);

    b = new wxBitmapButton(this, Enum::CP_Capture_Button_ID, normal,
                           wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    b->SetBitmapDisabled(disabled);

    t = new wxStaticText(this, wxID_ANY, "Capture");

    wxFontInfo fontInfo(10);
    fontInfo.Family(wxFONTFAMILY_DEFAULT).FaceName("Roboto").Light();
    wxFont font(fontInfo);

    t->SetFont(font);

    hSizer->Add(b, 1, wxEXPAND);
    // hSizer->Add(t, 0, wxEXPAND);

    vSizer->Add(hSizer, 0, wxALIGN_CENTER_HORIZONTAL);
    vSizer->Add(t, 0, wxALIGN_CENTER_HORIZONTAL);

    SetSizer(vSizer);
    Fit();
}

TB::~TB() {}

wxBitmap TB::recolor(wxBitmap &b, wxColour &c) {
    wxImage img = b.ConvertToImage();
    img.Replace(255, 255, 255, c.Red(), c.Green(), c.Blue());
    return wxBitmap(img);
}

wxBitmap TB::rescale(wxBitmap &b, wxSize &s) {
    wxImage img = b.ConvertToImage();
    img.Rescale(s.GetWidth(), s.GetHeight());
    return wxBitmap(img);
}

void TB::update(ButtonState state) {
    if (state == ButtonState::NORMAL) {
        setNormal();
    } else if (state == ButtonState::ACTIVE) {
        setActive();
    } else if (state == ButtonState::DISABLED) {
        setDisabled();
    } else
        throw new std::runtime_error("Invalid ButtonState");
}

void TB::setNormal() { b->SetBitmap(normal); }

void TB::setActive() { b->SetBitmap(active); }

void TB::setDisabled() { b->Disable(); }
