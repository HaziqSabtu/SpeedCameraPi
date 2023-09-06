#include <UI/Dialog/DialogBase.hpp>

DialogBaseYesNo::DialogBaseYesNo(wxWindow *parent, const wxString &title,
                                 const wxString &text)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {
    result = false;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *staticText = new wxStaticText(
        this, wxID_ANY, text, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    sizer->Add(staticText, 0, wxALL, 10);

    buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *yesButton = new wxButton(this, wxID_YES, "Yes");
    buttonSizer->Add(yesButton, 0, wxALL, 5);

    wxButton *noButton = new wxButton(this, wxID_NO, "No");
    buttonSizer->Add(noButton, 0, wxALL, 5);

    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(sizer);

    yesButton->Bind(wxEVT_BUTTON, &DialogBaseYesNo::OnYesButton, this);
    noButton->Bind(wxEVT_BUTTON, &DialogBaseYesNo::OnNoButton, this);

    staticText->Wrap(GetSize().GetWidth() - 20);
}

bool DialogBaseYesNo::GetConfirmationResult() const { return result; }

void DialogBaseYesNo::OnYesButton(wxCommandEvent &event) {
    result = true;
    EndModal(wxID_YES);
}

void DialogBaseYesNo::OnNoButton(wxCommandEvent &event) {
    result = false;
    EndModal(wxID_NO);
}