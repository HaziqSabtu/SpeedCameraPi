#include "UI/Dialog/SwitchModeDialog.hpp"

SwitchModeDialog::SwitchModeDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::SwitchMode::Title,
                      Data::Dialog::SwitchMode::Text) {}