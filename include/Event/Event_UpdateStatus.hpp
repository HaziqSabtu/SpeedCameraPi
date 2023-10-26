#pragma once

#include <UI/Layout/StatusPanel.hpp>
#include <wx/event.h>
#include <wx/string.h>

/**
 * @brief Data Event for Updating Status Panel
 *
 */
class UpdateStatusEvent;
wxDECLARE_EVENT(c_UPDATE_STATUS_EVENT, UpdateStatusEvent);

enum UPDATE_STATUS_EVENT_TYPE { UPDATE_STATUS = 1 };

class UpdateStatusEvent : public wxCommandEvent {
  public:
    static void Submit(wxEvtHandler *handler, const wxString &status,
                       int id = 1);

  public:
    UpdateStatusEvent(wxEventType eventType = c_UPDATE_STATUS_EVENT,
                      int id = 1);
    UpdateStatusEvent(const UpdateStatusEvent &e);
    virtual wxEvent *Clone() const;

    void SetStatus(const wxString &status);

    wxString GetStatus() const;

  private:
    wxString status;
};

typedef void (wxEvtHandler::*UpdateStatusFunction)(UpdateStatusEvent &);
#define UpdateStatusHandler(func)                                              \
    wxEVENT_HANDLER_CAST(UpdateStatusFunction, func)
#define EVT_UPDATE_STATUS(id, func)                                            \
    wx__DECLARE_EVT1(c_UPDATE_STATUS_EVENT, id, UpdateStatusHandler(func))
