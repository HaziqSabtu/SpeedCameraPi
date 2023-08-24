#pragma once

#include "UI/Button/TextButton/Type2/TextButtonT2.hpp"
#include "UI/Layout/TitlePanel.hpp"
#include "UI/Panel/Common/OKCancelPanel.hpp"
#include "UI/Panel/SettingsPanel/SettingsPanel.hpp"
#include "Utils/wxUtils.hpp"
#include <wx/gdicmn.h>
#include <wx/gtk/stattext.h>
#include <wx/hyperlink.h>

#include <wx/wx.h>

class InfoPanel : public wxPanel {
  public:
    InfoPanel(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText *topSpacer = new wxStaticText(
            this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));
        mainSizer->Add(topSpacer, 1, wxEXPAND);

        // insert icon
        wxSize s(256, 0);
        wxBitmap icon(
            wxT("Assets/speed_512_flat.png"),
            wxBITMAP_TYPE_PNG); // Replace "icon.png" with your icon file
        icon = Utils::resize(icon, s);

        wxStaticBitmap *iconBitmap = new wxStaticBitmap(this, wxID_ANY, icon);

        wxFontInfo f(25);
        f.Bold();
        wxFont font(f);

        mainSizer->Add(iconBitmap, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

        wxString titleText = "SpeedCameraPi";

        wxStaticText *title = new wxStaticText(this, wxID_ANY, titleText);
        title->SetFont(font);
        mainSizer->Add(title, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);

        mainSizer->AddSpacer(10);

        // Create clickable links
        wxHyperlinkCtrl *contact =
            new wxHyperlinkCtrl(this, wxID_ANY, "contact: email...",
                                "mailto:your.email@example.com");
        wxHyperlinkCtrl *docs = new wxHyperlinkCtrl(
            this, wxID_ANY, "Docs: link", "http://docs-link");
        wxHyperlinkCtrl *repo = new wxHyperlinkCtrl(
            this, wxID_ANY, "Repo: link", "http://repo-link");
        wxHyperlinkCtrl *paper = new wxHyperlinkCtrl(
            this, wxID_ANY, "Paper: link", "http://paper-link");
        wxHyperlinkCtrl *otherRepo = new wxHyperlinkCtrl(
            this, wxID_ANY, "Other repository: link", "http://other-repo-link");

        mainSizer->Add(contact, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM,
                       10);
        mainSizer->Add(docs, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM,
                       10);
        mainSizer->Add(repo, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM,
                       10);
        mainSizer->Add(paper, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM,
                       10);
        mainSizer->Add(otherRepo, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT | wxBOTTOM,
                       10);

        wxStaticText *bottomSpacer = new wxStaticText(
            this, wxID_ANY, "", wxDefaultPosition, wxSize(10, 10));

        mainSizer->Add(bottomSpacer, 1, wxEXPAND);

        SetSizerAndFit(mainSizer);
    }

    ~InfoPanel() {}

  private:
    wxBoxSizer *mainSizer;
};

class InfoFrame : public wxFrame {
  public:
    InfoFrame();

    TitlePanel *title_panel;

    InfoPanel *info_panel;

    //SettingsScrollPanel *scrolled_panel;

    TextButton *back_button;

  private:
    void OnButton(wxCommandEvent &e);

    const PanelID panel_id = PanelID::PANEL_INFO;

    DECLARE_EVENT_TABLE()
};