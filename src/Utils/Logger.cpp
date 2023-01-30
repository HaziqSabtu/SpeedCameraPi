#include <Utils/Logger.hpp>

AppLogger::AppLogger() {
    wxString logFileName = wxDateTime::Now().Format("log_%Y%m%d_%H%M%S.txt");
    m_logFile.Open(logFileName, wxFile::write);
    m_streambuf = new MyStreambuf(m_logFile);
    m_coutBuf = std::cout.rdbuf(m_streambuf);
}

void AppLogger::DoLogText(const wxString &msg) {
    wxString logLine =
        wxDateTime::Now().FormatISOCombined(' ') + ": " + msg + "\n";
    m_logFile.Write(logLine);
}

// void AppLogger::Flush() {
//     wxLog::Flush();
//     std::cout.rdbuf(m_coutBuf);
//     m_logFile.Close();
// }