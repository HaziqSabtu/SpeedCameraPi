#include "UI/Dialog/RemoveRoiDialog.hpp"

RemoveRoiDialog::RemoveRoiDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::RemoveRoi::Title,
                      Data::Dialog::RemoveRoi::Text) {}