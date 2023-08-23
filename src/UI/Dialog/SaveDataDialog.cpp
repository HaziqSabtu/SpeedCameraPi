#include <UI/Dialog/SaveDataDialog.hpp>

SaveDataDialog::SaveDataDialog(wxWindow *parent, wxString s)
    : DialogBaseYesNo(parent, Data::Dialog::SaveData::Title,
                      Data::Dialog::SaveData::Text(s)) {}