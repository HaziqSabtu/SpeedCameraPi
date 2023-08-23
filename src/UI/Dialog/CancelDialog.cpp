#include <UI/Dialog/CancelDialog.hpp>

CancelDialog::CancelDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::Cancel::Title,
                      Data::Dialog::Cancel::Text) {}