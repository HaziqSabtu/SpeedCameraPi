#include <Utils/wxUtils.hpp>

namespace Utils {
std::string wxStringToString(wxString wxstr) {
    std::string str;
    str.assign(wxstr.mb_str());
    return str;
}
} // namespace Utils
