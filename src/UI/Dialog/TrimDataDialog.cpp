#include "UI/Dialog/TrimDataDialog.hpp"

TrimDataDialog::TrimDataDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::TrimData::Title,
                      Data::Dialog::TrimData::Text) {}