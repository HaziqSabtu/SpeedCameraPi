
#ifndef ERROR_EVENT_HPP
#define ERROR_EVENT_HPP

#include <string>
#include <wx/event.h>

class ErrorEvent;
wxDECLARE_EVENT(c_ERROR_EVENT, ErrorEvent);

class ErrorEvent : public wxCommandEvent {
  public:
    ErrorEvent(wxEventType eventType = c_ERROR_EVENT, int id = 1);
    ErrorEvent(const ErrorEvent& e);
    virtual wxEvent* Clone() const;

    void SetErrorData(const std::string& errorData);

    std::string GetErrorData() const;

  private:
    std::string errorData;
};

typedef void (wxEvtHandler::*ErrorFunction)(ErrorEvent&);
#define ErrorHandler(func) wxEVENT_HANDLER_CAST(ErrorFunction, func)
#define EVT_ERROR(id, func)                                               \
    wx__DECLARE_EVT1(c_ERROR_EVENT, id, ErrorHandler(func))
#endif