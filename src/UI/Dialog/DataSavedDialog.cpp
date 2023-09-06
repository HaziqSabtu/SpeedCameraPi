#include "UI/Dialog/DataSavedDialog.hpp"

DataSavedDialog::DataSavedDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::DataSaved::Title,
                      Data::Dialog::DataSaved::Text) {

    resetButton = new wxButton(this, resetButtonID, "Reset Session");

    buttonSizer->Add(resetButton, 0, wxALL, 5);

    resetButton->Bind(wxEVT_BUTTON, &DataSavedDialog::OnResetButton, this);
}

void DataSavedDialog::OnResetButton(wxCommandEvent &event) {
    result = true;
    EndModal(resetButtonID);
}
