
#include <Event/Event_Error.hpp>

wxDEFINE_EVENT(c_ERROR_EVENT, ErrorEvent);

ErrorEvent::ErrorEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

ErrorEvent::ErrorEvent(const ErrorEvent &e) : wxCommandEvent(e) {
    this->SetErrorData(e.GetErrorData());
}

wxEvent *ErrorEvent::Clone() const { return new ErrorEvent(*this); }

void ErrorEvent::SetErrorData(const std::string &errorData) {
    this->errorData = errorData;
}

std::string ErrorEvent::GetErrorData() const { return this->errorData; }

void ErrorEvent::Submit(wxEvtHandler *handler, const std::string &errorData,
                        int id) {
    ErrorEvent event(c_ERROR_EVENT, id);
    event.SetErrorData(errorData);
    wxPostEvent(handler, event);
}
