#ifndef HOUGH_EVENT_HPP
#define HOUGH_EVENT_HPP

#include <Utils/DataStruct.hpp>
#include <wx/event.h>

class HoughEvent;
wxDECLARE_EVENT(c_HOUGH_EVENT, HoughEvent);

enum HOUGH_EVENT_TYPE { HOUGH_START = 1, HOUGH_END };

class HoughEvent : public wxCommandEvent {
  public:
    HoughEvent(wxEventType eventType = c_HOUGH_EVENT, int id = 1);
    HoughEvent(const HoughEvent &e);
    virtual wxEvent *Clone() const;

    void SetImageData(std::vector<ImageData> *imgData);

    std::vector<ImageData> *GetImageData() const;

  private:
    std::vector<ImageData> *imgData;
};

typedef void (wxEvtHandler::*HoughFunction)(HoughEvent &);
#define HoughHandler(func) wxEVENT_HANDLER_CAST(HoughFunction, func)
#define EVT_HOUGH(id, func)                                                    \
    wx__DECLARE_EVT1(c_HOUGH_EVENT, id, HoughHandler(func))
#endif