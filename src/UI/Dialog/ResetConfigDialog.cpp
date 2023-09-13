#include "UI/Dialog/ResetConfigDialog.hpp"

ResetConfigDialog::ResetConfigDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::ResetConfig::Title,
                      Data::Dialog::ResetConfig::Text) {}