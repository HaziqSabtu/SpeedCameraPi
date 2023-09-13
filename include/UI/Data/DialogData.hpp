#pragma once

#include <UI/Data/Data.hpp>

namespace Data {
namespace Dialog {
namespace Confirmation {
const wxString title = "Confirmation";
const wxString yes = "Yes";
const wxString no = "No";
} // namespace Confirmation

namespace Cancel {
const wxString Title = "Cancel";
const wxString Text = "Any unsaved changes will be lost. Are you sure ?";
} // namespace Cancel

namespace SaveData {
const wxString Title = "Save Data";
inline const wxString Text(wxString s) {
    return wxString::Format("File will be saved as %s", s);
}
} // namespace SaveData

namespace ResetData {
const wxString Title = "Reset";
const wxString Text = "Are you sure you want to reset current session? All "
                      "unsaved changes will be lost.";
} // namespace ResetData

namespace RemoveCalibration {
const wxString Title = "Remove Calibration";
const wxString Text = "Are you sure you want to remove current calibration? "
                      "This action cannot be undone.";
} // namespace RemoveCalibration

namespace RemoveRoi {
const wxString Title = "Remove ROI";
const wxString Text = "Are you sure you want to remove current ROI? This "
                      "action cannot be undone.";
} // namespace RemoveRoi

namespace DataSaved {
const wxString Title = "Data Saved";
const wxString Text = "Data saved successfully. Do you want to clear current "
                      "session and start a new one?";
} // namespace DataSaved

namespace TrimData {
const wxString Title = "Trim Data";
const wxString Text =
    "Trimming Data requires the Roi and Calibration data to be "
    "removed. Do you want to continue? This action cannot be undone.";
} // namespace TrimData

namespace ResetConfig {
const wxString Title = "Reset Config";
const wxString Text = "Are you sure you want to reset the configuration? "
                      "This action cannot be undone.";
} // namespace ResetConfig

namespace ExitApp {
const wxString Title = "Exit";
const wxString Text = "Are you sure you want to exit the application?";
} // namespace ExitApp

} // namespace Dialog
} // namespace Data