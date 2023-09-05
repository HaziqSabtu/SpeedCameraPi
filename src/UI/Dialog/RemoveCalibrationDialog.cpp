#include "UI/Dialog/RemoveCalibrationDialog.hpp"

RemoveCalibrationDialog::RemoveCalibrationDialog(wxWindow *parent)
    : DialogBaseYesNo(parent, Data::Dialog::RemoveCalibration::Title,
                      Data::Dialog::RemoveCalibration::Text) {}