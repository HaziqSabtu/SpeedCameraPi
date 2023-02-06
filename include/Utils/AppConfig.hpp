#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include <wx/file.h>
#include <wx/fileconf.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

class AppConfig {
  public:
    AppConfig();
    ~AppConfig();

    std::string GetFileName() {
        wxString fileName;
        config->Read("FileName", &fileName);
        return fileName.ToStdString();
    }

    std::string GetDirLocation() {
        wxString dirLocation;
        config->Read("DirLocation", &dirLocation);
        return dirLocation.ToStdString();
    }

  private:
    wxFileConfig *config;
};

#endif