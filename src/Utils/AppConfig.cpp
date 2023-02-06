#include <Utils/AppConfig.hpp>

AppConfig::AppConfig() {
    wxString ini_filename = wxStandardPaths::Get().GetUserConfigDir() +
                            wxFileName::GetPathSeparator() + "config.ini";

    if (!wxFile::Exists(ini_filename)) {
        wxLogMessage(wxT("creating inifile: %s"), ini_filename);
        config = new wxFileConfig("", "", ini_filename);
        config->Write("FileName", "test.avi");
        config->Write("DirLocation", "/");
        config->Flush();
    } else {
        wxLogMessage(wxT("loading inifile: %s"), ini_filename);
        config = new wxFileConfig("", "", ini_filename);
    }
}

AppConfig::~AppConfig() { delete config; }