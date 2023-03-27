#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Utils/Logger/StreamBuff.hpp>
#include <wx/file.h>
#include <wx/log.h>
#include <wx/wx.h>

class AppLogger : public wxLog {
  public:
    // getcurrent time as file name withour regex

    AppLogger();

    virtual void DoLogText(const wxString &msg);

  private:
    wxFile m_logFile;
    AppStreamBuf *m_streambuf;
    std::streambuf *m_coutBuf;
};

#endif

/**
 * redirecting cout to wxLogMessage
 *
 */