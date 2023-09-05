#pragma once

#include <UI/Theme/Data.hpp>

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
const wxString Title = "Save";
inline const wxString Text(wxString s) {
    return wxString::Format("Save %s ?", s);
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

// namespace SaveData
// namespace Cancel
} // namespace Dialog
} // namespace Data