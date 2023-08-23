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

// namespace SaveData
// namespace Cancel
} // namespace Dialog
} // namespace Data