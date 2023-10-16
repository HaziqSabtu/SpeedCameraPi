#include <UI/Dialog/ConfirmationDialog.hpp>

ConfirmationDialog::ConfirmationDialog(wxWindow *parent,
                                       const wxString &message)
    : wxDialog(parent, wxID_ANY, "Confirmation", wxDefaultPosition,
               wxDefaultSize) {
    result = false;

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *staticText = new wxStaticText(this, wxID_ANY, message);
    sizer->Add(staticText, 0, wxALL, 10);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton *yesButton = new wxButton(this, wxID_YES, "Yes");
    buttonSizer->Add(yesButton, 0, wxALL, 5);

    wxButton *noButton = new wxButton(this, wxID_NO, "No");
    buttonSizer->Add(noButton, 0, wxALL, 5);

    sizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizerAndFit(sizer);

    yesButton->Bind(wxEVT_BUTTON, &ConfirmationDialog::OnYesButton, this);
    noButton->Bind(wxEVT_BUTTON, &ConfirmationDialog::OnNoButton, this);
}

bool ConfirmationDialog::GetConfirmationResult() const { return result; }

void ConfirmationDialog::OnYesButton(wxCommandEvent &event) {
    result = true;
    EndModal(wxID_YES);
}

void ConfirmationDialog::OnNoButton(wxCommandEvent &event) {
    result = false;
    EndModal(wxID_NO);
}