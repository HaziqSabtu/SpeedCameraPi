#include <Utils/AppConfig.hpp>

AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "config.ini";

    if (!wxFile::Exists(ini_filename)) {
        config = new wxFileConfig("", "", ini_filename);
        config->Write("FileName", "test.avi");
        config->Write("DirLocation", "/");
        config->Flush();
    } else {
        config = new wxFileConfig("", "", ini_filename);
    }
}

AppConfig::~AppConfig() { delete config; }