#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

/**
 * @brief Data Event for updating Result Panel with Speed Value
 *
 */
class UpdateSpeedEvent;
wxDECLARE_EVENT(c_UPDATE_SPEED_EVENT, UpdateSpeedEvent);

class UpdateSpeedEvent : public wxCommandEvent {
  public:
    static void Submit(wxEvtHandler *handler, const double spd, int id = 1);

    UpdateSpeedEvent(wxEventType eventType = c_UPDATE_SPEED_EVENT, int id = 1);
    UpdateSpeedEvent(const UpdateSpeedEvent &e);
    virtual wxEvent *Clone() const;

    void SetSpeed(const double spd);

    double GetSpeed() const;

  private:
    double speed;
};

typedef void (wxEvtHandler::*UpdateSpeedFunction)(UpdateSpeedEvent &);
#define UpdateSpeedHandler(func) wxEVENT_HANDLER_CAST(UpdateSpeedFunction, func)
#define EVT_UPDATE_SPEED(id, func)                                             \
    wx__DECLARE_EVT1(c_UPDATE_SPEED_EVENT, id, UpdateSpeedHandler(func))
