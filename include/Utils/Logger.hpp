#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <wx/file.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/wx.h>

class Logger : public wxLog {
  public:
    Logger() : wxLog() {
        wxString cwd = wxFileName::GetCwd();
        // wxLogMessage("Current working directory: %s", cwd);
    }

    virtual void DoLogText(const wxString &msg) {
        wxString filepath = wxFileName::GetCwd() + "\\log.txt";
        wxLogMessage("log file path: %s", filepath);
        wxFile file(filepath, wxFile::write_append);
        if (!file.IsOpened()) {
            wxLogError("Failed to open log file %s", filepath);
            return;
        }
        file.Write(msg);
        file.Write("\n");
        file.Close();
    }
};

#endif