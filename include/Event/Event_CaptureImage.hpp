#ifndef CAPTURE_IMAGE_EVENT_HPP
#define CAPTURE_IMAGE_EVENT_HPP

#include <Utils/DataStruct.hpp>
#include <wx/event.h>

class CaptureImageEvent;
wxDECLARE_EVENT(c_CAPTURE_IMAGE_EVENT, CaptureImageEvent);

enum CAPTURE_IMAGE_TYPE { CAPTURE_START = 1, CAPTURE_END };

class CaptureImageEvent : public wxCommandEvent {
  public:
    CaptureImageEvent(wxEventType eventType = c_CAPTURE_IMAGE_EVENT,
                      int id = 1);
    CaptureImageEvent(const CaptureImageEvent &e);
    virtual wxEvent *Clone() const;

    void SetImageData(std::vector<ImageData> *imgData);

    std::vector<ImageData> *GetImageData() const;

  private:
    std::vector<ImageData> *imgData;
};

// https://docs.wxwidgets.org/3.2/overview_events.html#overview_events_custom_ownclass
typedef void (wxEvtHandler::*CaptureImageFunction)(CaptureImageEvent &);
#define CaptureImageHandler(func)                                              \
    wxEVENT_HANDLER_CAST(CaptureImageFunction, func)
#define EVT_CAPTUREIMAGE(id, func)                                             \
    wx__DECLARE_EVT1(c_CAPTURE_IMAGE_EVENT, id, CaptureImageHandler(func))
#endif