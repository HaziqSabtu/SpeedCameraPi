#include "UI/Dialog/ResetDataDialog.hpp"

ResetDataDialog::ResetDataDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::ResetData::Title,
                      Data::Dialog::ResetData::Text) {}