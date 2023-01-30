#include <Utils/Logger.hpp>

AppLogger::AppLogger() {
    wxString logFileName = wxDateTime::Now().Format("log_%Y%m%d_%H%M%S.txt");
    m_logFile.Open(logFileName, wxFile::write);
}

void AppLogger::DoLogText(const wxString &msg) {
    wxString logLine =
        wxDateTime::Now().FormatISOCombined(' ') + ": " + msg + "\n";
    m_logFile.Write(logLine);
}