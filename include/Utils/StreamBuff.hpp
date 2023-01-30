#ifndef APP_STREAM_BUFF_HPP
#define APP_STREAM_BUFF_HPP

#include <iostream>
#include <streambuf>
#include <wx/file.h>
#include <wx/wx.h>

class MyStreambuf : public std::streambuf {
  public:
    MyStreambuf(wxFile &file) : m_file(file) {}

    virtual int_type overflow(int_type ch) {
        if (ch != EOF) {
            char c = static_cast<char>(ch);
            m_file.Write(&c, 1);
        }
        return ch;
    }

  private:
    wxFile &m_file;
};

#endif