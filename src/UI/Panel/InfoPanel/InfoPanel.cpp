#include <UI/Panel/InfoPanel/InfoPanel.hpp>

/**
 * @brief Construct a new Info Panel:: Info Panel object
 *
 * @param parent Pointer to the parent window
 * @param id ID of the panel
 */
InfoPanel::InfoPanel(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *topSpacer = new Spacer(this);
    mainSizer->Add(topSpacer, 1, wxEXPAND);

    wxBitmap icon(Data::Info::logo);
    icon = Utils::resize(icon, Data::Info::iconSize);
    wxStaticBitmap *iconBitmap = new wxStaticBitmap(this, wxID_ANY, icon);

    wxBitmap thb(Data::Info::thbLogo);
    thb = Utils::resize(thb, Data::Info::iconSize);
    wxStaticBitmap *thbBitmap = new wxStaticBitmap(this, wxID_ANY, thb);

    wxStaticText *title = new wxStaticText(this, wxID_ANY, Data::Info::Title);

    AppFont titleFont(Data::Info::TitleFontData);
    title->SetFont(titleFont);

    wxHyperlinkCtrl *contact =
        new HyperLinkCtrl(this, wxID_ANY, Data::Info::contact);
    wxHyperlinkCtrl *docs = new HyperLinkCtrl(this, wxID_ANY, Data::Info::docs);
    wxHyperlinkCtrl *repo = new HyperLinkCtrl(this, wxID_ANY, Data::Info::repo);
    wxHyperlinkCtrl *paper =
        new HyperLinkCtrl(this, wxID_ANY, Data::Info::paper);
    wxHyperlinkCtrl *otherRepo =
        new HyperLinkCtrl(this, wxID_ANY, Data::Info::otherRepo);

    mainSizer->Add(iconBitmap, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    mainSizer->Add(thbBitmap, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
    mainSizer->Add(title, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

    mainSizer->Add(contact, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(docs, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(repo, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(paper, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    mainSizer->Add(otherRepo, 0,
                   wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    wxStaticText *bottomSpacer = new Spacer(this);
    mainSizer->Add(bottomSpacer, 1, wxEXPAND);

    SetSizerAndFit(mainSizer);
}

/**
 * @brief Destroy the Info Panel:: Info Panel object
 *
 */
InfoPanel::~InfoPanel() {}