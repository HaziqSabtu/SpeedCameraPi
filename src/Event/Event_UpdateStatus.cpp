#include <Event/Event_UpdateStatus.hpp>

wxDEFINE_EVENT(c_UPDATE_STATUS_EVENT, UpdateStatusEvent);

UpdateStatusEvent::UpdateStatusEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

UpdateStatusEvent::UpdateStatusEvent(const UpdateStatusEvent &e)
    : wxCommandEvent(e) {
    this->SetStatus(e.GetStatus());
}

wxEvent *UpdateStatusEvent::Clone() const {
    return new UpdateStatusEvent(*this);
}

void UpdateStatusEvent::SetStatus(const wxString &status) {
    this->status = status;
}

wxString UpdateStatusEvent::GetStatus() const { return this->status; }

void UpdateStatusEvent::Submit(wxEvtHandler *handler, const wxString &status,
                               int id) {
    UpdateStatusEvent event(c_UPDATE_STATUS_EVENT, UPDATE_STATUS);
    event.SetStatus(status);
    wxPostEvent(handler, event);
}